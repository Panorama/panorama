import Qt 4.7

Rectangle {
    id: dialog
    property QtObject milky
    property bool active: false

    signal activate()
    signal deactivate()
    signal yes()
    signal no()

    onActivate: active = true
    onDeactivate: active = false

    function upgrade(pndId) {
        milky.addTarget(pndId);
        activate();
    }

    function upgradeAll() {
        milky.addUpgradableTargets();
        activate();
    }

    color: Qt.rgba(0.1,0.1,0.1,0.8)

    Loader {
        sourceComponent: dialog.active ? dialogContent : null
        anchors.fill: parent
    }

    Component {
        id: dialogContent

        Item {
            anchors.fill: parent

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }


            Component.onCompleted: {
                var targets = milky.getTargetPackages();
                if(targets.length > 0) {
                    upgradeVerify.upgradedPackages = targets;
                    state = "verify";
                } else {
                    milky.clearTargets();
                    dialog.deactivate();
                }

                dialog.yes.connect(function() {
                    if(state == "verify") {
                        dialog.milky.upgrade();
                        dialog.deactivate();
                    }
                });

                dialog.no.connect(function() {
                    if(state == "verify") {
                        deactivate();
                        dialog.milky.clearTargets();
                    }
                });
            }

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
                    id: upgradeNoButton
                    anchors.top: upgradeVerifyLabel.bottom
                    anchors.right: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    color: "#ecc"
                    label: "No"
                    controlHint: "X"
                    onClicked: {
                        dialog.no();
                    }
                }
                Button {
                    id: upgradeYesButton
                    anchors.top: upgradeVerifyLabel.bottom
                    anchors.left: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    color: "#cec"
                    label: "Yes"
                    controlHint: "B"
                    onClicked: {
                        dialog.yes();
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
        }
    }
}
