import Qt 4.7

Rectangle {
    id: dialog
    property QtObject milky
    property QtObject installDirectorySetting

    signal activate()
    signal deactivate()

    function install(pndId) {
        milky.install(pndId);
        activate();
    }

    function yes() {
        if(state == "verify") {
            installYesButton.clicked(false);
        } else if(state == "done") {
            installDoneButton.clicked(false);
        }
    }

    function no() {
        if(state == "verify") {
            installNoButton.clicked(false);
        }
    }

    // Restrict mouse events to children
    MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

    color: Qt.rgba(0.1,0.1,0.1,0.8)

    Component.onCompleted: {
        milky.events.installCheck.connect(function() {
            var targets = milky.getTargetPackages();
            if(targets.length == 1) {
                state = "verify";
                installVerify.installedPackage = targets[0].title;
            } else {
                milky.answer(false);
                milky.clearTargets();
            }
        });
        milky.events.downloadStarted.connect(function(pnd) {
            state = "download";
            installDownload.progress = 0;
            installDownload.pnd = pnd; // Contains only title because of Qt bug http://bugreports.qt.nokia.com/browse/QTBUG-15712
        });
        milky.events.downloadFinished.connect(function() {
            state = "apply";
        });
        milky.events.installDone.connect(function() {
            state = "done";
        });

    }

    states: [
        State {
            name: "verify"
            PropertyChanges { target: installVerify; opacity: 1.0 }
            PropertyChanges { target: installApply; opacity: 0.0 }
            PropertyChanges { target: installDownload; opacity: 0.0; progress: 0 }
            PropertyChanges { target: installDone; opacity: 0.0 }

        },
        State {
            name: "download"
            PropertyChanges { target: installVerify; opacity: 0.0 }
            PropertyChanges { target: installApply; opacity: 0.0 }
            PropertyChanges { target: installDownload; opacity: 1.0 }
            PropertyChanges { target: installDone; opacity: 0.0 }
        },
        State {
            name: "apply"
            PropertyChanges { target: installVerify; opacity: 0.0 }
            PropertyChanges { target: installDownload; opacity: 0.0 }
            PropertyChanges { target: installApply; opacity: 1.0 }
            PropertyChanges { target: installDone; opacity: 0.0 }
        },
        State {
            name: "done"
            PropertyChanges { target: installVerify; opacity: 0.0 }
            PropertyChanges { target: installDownload; opacity: 0.0 }
            PropertyChanges { target: installApply; opacity: 0.0 }
            PropertyChanges { target: installDone; opacity: 1.0 }
        }
    ]

    state: "verify"

    Item {
        id: installVerify
        anchors.centerIn: parent
        height: childrenRect.height
        property string installedPackage: ""

        Text {
            id: installVerifyLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Install PND " + parent.installedPackage + "?"
            font.pixelSize: 24
            color: "#eee"
        }
        Button {
            id: installNoButton
            anchors.top: installVerifyLabel.bottom
            anchors.right: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#ecc"
            label: "No"
            controlHint: "A"
            onClicked: {
                milky.answer(false);
                milky.clearTargets();
                dialog.deactivate();
            }
        }
        Button {
            id: installYesButton
            anchors.top: installVerifyLabel.bottom
            anchors.left: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#cec"
            label: "Yes"
            controlHint: "B"
            onClicked: {
                milky.answer(true);
            }
        }

        Row {
            id: installDirectoryButtons
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: installYesButton.bottom
            anchors.margins: 16
            height: childrenRect.height
            spacing: 8
            Repeater {
                model: ["apps", "desktop", "menu"]
                delegate: Button {
                    width: 96
                    label: modelData
                    pressed: installDirectorySetting.value == label
                    onClicked: installDirectorySetting.value = label
                }
            }
        }

    }

    Item {
        id: installDownload
        property string pnd: ""  // Contains only PND title because of Qt bug http://bugreports.qt.nokia.com/browse/QTBUG-15712
        property int progress: 0
        anchors.centerIn: parent
        height: childrenRect.height

        Timer {
            running: dialog.state == "download"
            interval: 100
            repeat: true
            onTriggered: {
                if(milky.bytesToDownload) {
                    installDownload.progress = parseInt(100.0 * milky.bytesDownloaded / milky.bytesToDownload)
                }
            }

        }

        Text {
            id: installDownloadLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: installDownload.pnd ? "Downloading " + installDownload.pnd +"..." : ""
            font.pixelSize: 24
            color: "#eee"
        }

        Row {
            id: installPercentageIndicator
            anchors.top: installDownloadLabel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 16
            spacing: 8
            Repeater {
                model: 10
                delegate: Rectangle {
                    function calcValue() {
                        if(installDownload.progress >= 10 * (index+1))
                            return 1.0
                        else if(installDownload.progress < 10 * index)
                            return 0.0
                        else
                            return (installDownload.progress % 10) / 10.0
                    }

                    property real value: calcValue()

                    height: 32
                    width: 16
                    radius: 6
                    smooth: true
                    gradient: Gradient {
                        GradientStop { position: 0; color: Qt.rgba(0.5+(1.0-value)*0.5, 0.5+value*0.5, 0.5, 1.0) }
                        GradientStop { position: 1; color: Qt.rgba(0.5+(1.0-value)*0.8*0.5, 0.5+value*0.8*0.5, 0.5, 1.0) }
                    }
                }
            }
        }

        Text {
            id: installPercentage

            anchors.top: installPercentageIndicator.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 16
            text: installDownload.progress + "%"
            font.pixelSize: 24
            color: "#eee"
        }

    }

    Item {
        id: installApply
        anchors.centerIn: parent
        height: childrenRect.height

        Text {
            id: installProgressLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Installing..."
            font.pixelSize: 24
            color: "#eee"
        }
    }

    Item {
        id: installDone
        anchors.centerIn: parent
        height: childrenRect.height

        Text {
            id: installDoneLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Install complete"
            font.pixelSize: 24
            color: "#eee"
        }
        Button {
            id: installDoneButton
            anchors.top: installDoneLabel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#eee"
            label: "Continue"
            controlHint: "B"
            onClicked: {
                dialog.deactivate()
            }
        }
    }


}
