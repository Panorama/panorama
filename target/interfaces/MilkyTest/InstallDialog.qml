import Qt 4.7

Rectangle {
    id: dialog
    property QtObject milky

    signal activate()
    signal deactivate()

    function install(pndId, title) {
        installVerify.installedPackage = title;
        milky.install(pndId);
    }

    // Restrict mouse events to children
    MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

    color: "#222"

    Component.onCompleted: {
        milky.events.installCheck.connect(function() {
            activate();
            state = "verify";
        });
        milky.events.installStart.connect(function() {
            activate();
            state = "download";
        });
        milky.events.downloadFinished.connect(function() {
            activate();
            state = "apply";
        });
        milky.events.installDone.connect(function() {
            activate();
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
            id: installYesButton
            anchors.top: installVerifyLabel.bottom
            anchors.right: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#cec"
            label: "Yes"
            onClicked: {
                milky.answer(true);
            }
        }
        Button {
            id: installNoButton
            anchors.top: installVerifyLabel.bottom
            anchors.left: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#ecc"
            label: "No"
            onClicked: {
                milky.answer(false);
                dialog.deactivate()
            }
        }

    }

    Item {
        id: installDownload
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
            text: "Downloading..."
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
            text: "Applying..."
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
            onClicked: {
                dialog.deactivate()
            }
        }
    }


}
