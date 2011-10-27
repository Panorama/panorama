import Qt 4.7

Rectangle {
    id: dialog
    property QtObject milky
    property QtObject installDirectorySetting
    property bool active: false

    signal activate()
    signal deactivate()
    signal verifyInstall(string title)

    onActivate: active = true
    onDeactivate: active = false

    function install(pndId) {
        milky.clearTargets();
        milky.addTarget(pndId);
        activate();
    }

    function yes() {
        milky.install();
        deactivate();
    }

    function no() {
        milky.clearTargets();
        deactivate();
    }


    // Restrict mouse events to children
    MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

    color: Qt.rgba(0.1,0.1,0.1,0.8)

    Component.onCompleted: {
        activate.connect(function() {
            var targets = milky.getTargetPackages();
            if(targets.length == 1) {
                state = "verify";
                verifyInstall(targets[0].title);
            } else {
                milky.clearTargets();
                dialog.deactivate();
            }
        });

        milky.events.installCheck.connect(function() {
            dialog.milky.answer(true);
        });
    }

    Loader {
        anchors.centerIn: parent
        sourceComponent: dialog.active ? dialogContent : null
    }

    Component {
        id: dialogContent

        Item {
            id: installVerify
            height: childrenRect.height

            Component.onCompleted: {
                dialog.verifyInstall.connect(function(title) {
                    installVerifyLabel.text = "Install PND " + title + "?"
                });
            }

            Text {
                id: installVerifyLabel
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: ""
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
                controlHint: "X"
                onClicked: {
                    dialog.no();
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
                    dialog.yes();
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
    }
}
