import Qt 4.7

Rectangle {
    id: dialog
    property QtObject milky

    signal activate()
    signal deactivate()

    function upgrade(pndId) {
        milky.upgrade(pndId);
    }


    // Restrict mouse events to children
    MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

    color: "#222"

    Component.onCompleted: {
        milky.events.upgradeCheck.connect(function() {
            var targets = milky.getTargetPackages();
            if(targets.length > 0) {
                upgradeVerify.upgradedPackages = targets;
                activate();
                state = "verify";
            } else {
                milky.answer(false);
                milky.clearTargets();
            }

        });
        milky.events.upgradeStart.connect(function() {
            activate();
            state = "download";
        });
        milky.events.downloadFinished.connect(function() {
            activate();
            state = "apply";
        });
        milky.events.upgradeDone.connect(function() {
            activate();
            state = "done";
        });

    }

    states: [
        State {
            name: "verify"
            PropertyChanges { target: upgradeVerify; opacity: 1.0 }
            PropertyChanges { target: upgradeApply; opacity: 0.0 }
            PropertyChanges { target: upgradeDownload; opacity: 0.0 }
            PropertyChanges { target: upgradeDone; opacity: 0.0 }
            PropertyChanges { target: upgradeDownload; progress: 0 }

        },
        State {
            name: "download"
            PropertyChanges { target: upgradeVerify; opacity: 0.0 }
            PropertyChanges { target: upgradeApply; opacity: 0.0 }
            PropertyChanges { target: upgradeDownload; opacity: 1.0 }
            PropertyChanges { target: upgradeDone; opacity: 0.0 }
        },
        State {
            name: "apply"
            PropertyChanges { target: upgradeVerify; opacity: 0.0 }
            PropertyChanges { target: upgradeDownload; opacity: 0.0 }
            PropertyChanges { target: upgradeApply; opacity: 1.0 }
            PropertyChanges { target: upgradeDone; opacity: 0.0 }
        },
        State {
            name: "done"
            PropertyChanges { target: upgradeVerify; opacity: 0.0 }
            PropertyChanges { target: upgradeDownload; opacity: 0.0 }
            PropertyChanges { target: upgradeApply; opacity: 0.0 }
            PropertyChanges { target: upgradeDone; opacity: 1.0 }
        }
    ]

    state: "verify"

    Item {
        id: upgradeVerify
        anchors.centerIn: parent
        height: childrenRect.height
        property variant upgradedPackages: []

        Text {
            id: upgradeVerifyLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: genText()
            font.pixelSize: 24
            color: "#eee"

            function genText() {
                if(upgradeVerify.upgradedPackages.length == 0) {
                    return "No upgrades"
                } else if(upgradeVerify.upgradedPackages.length == 1) {
                    return "Upgrade PND " + upgradeVerify.upgradedPackages[0].title + "?"
                } else {
                    return "Upgrade " + upgradeVerify.upgradedPackages.length + " PNDs?"
                }
            }
        }
        Button {
            id: upgradeYesButton
            anchors.top: upgradeVerifyLabel.bottom
            anchors.right: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#cec"
            label: "Yes"
            onClicked: {
                dialog.milky.answer(true);
            }
        }
        Button {
            id: upgradeNoButton
            anchors.top: upgradeVerifyLabel.bottom
            anchors.left: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#ecc"
            label: "No"
            onClicked: {
                dialog.milky.answer(false);
                dialog.deactivate();
                milky.clearTargets();
            }
        }
    }

    ListView {
        anchors.top: upgradeVerify.bottom
        anchors.bottom: parent.bottom
        anchors.left:parent.left
        anchors.right: parent.right
        anchors.margins: 16
        clip: true
        visible: upgradeVerify.opacity > 0 && upgradeVerify.upgradedPackages.length > 1
        model: upgradeVerify.upgradedPackages
        delegate: Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: modelData.title
            color: "#eee"
            font.pixelSize: 14
        }
    }

    Item {
        id: upgradeDownload
        property int progress: 0
        anchors.centerIn: parent
        height: childrenRect.height

        Timer {
            running: dialog.state == "download"
            interval: 100
            repeat: true
            onTriggered: {
                if(milky.bytesToDownload) {
                    upgradeDownload.progress = parseInt(100.0 * milky.bytesDownloaded / milky.bytesToDownload)
                }
            }

        }

        Text {
            id: upgradeDownloadLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Downloading..."
            font.pixelSize: 24
            color: "#eee"
        }

        Row {
            id: upgradePercentageIndicator
            anchors.top: upgradeDownloadLabel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 16
            spacing: 8
            Repeater {
                model: 10
                delegate: Rectangle {
                    function calcValue() {
                        if(upgradeDownload.progress >= 10 * (index+1))
                            return 1.0
                        else if(upgradeDownload.progress < 10 * index)
                            return 0.0
                        else
                            return (upgradeDownload.progress % 10) / 10.0
                    }

                    property real value: calcValue()

                    height: 32
                    width: 16
                    radius: 6
                    smooth: true
                    gradient: Gradient {
                        GradientStop { position: 0; color: Qt.rgba(0.5+(1.0-value)*0.5, 0.5, 0.5+value*0.5, 1.0) }
                        GradientStop { position: 1; color: Qt.rgba(0.5+(1.0-value)*0.8*0.5, 0.5, 0.5+value*0.8*0.5, 1.0) }
                    }
                }
            }
        }

        Text {
            id: upgradePercentage

            anchors.top: upgradePercentageIndicator.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.margins: 16
            text: upgradeDownload.progress + "%"
            font.pixelSize: 24
            color: "#eee"
        }

    }

    Item {
        id: upgradeApply
        anchors.centerIn: parent
        height: childrenRect.height

        Text {
            id: upgradeProgressLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Applying..."
            font.pixelSize: 24
            color: "#eee"
        }
    }

    Item {
        id: upgradeDone
        anchors.centerIn: parent
        height: childrenRect.height

        Text {
            id: upgradeDoneLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Upgrade complete"
            font.pixelSize: 24
            color: "#eee"
        }
        Button {
            id: upgradeDoneButton
            anchors.top: upgradeDoneLabel.bottom
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
