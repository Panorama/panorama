import Qt 4.7

Rectangle {
    id: dialog
    property QtObject milky
    property bool active: false

    signal activate()
    signal deactivate()

    onActivate: active = true
    onDeactivate: active = false

    function remove(pndId) {
        milky.addTarget(pndId);
        activate();
    }

    function yes() {
        if(state == "verify") {
            removeYesButton.clicked(false);
        } else if(state == "done") {
            removeDoneButton.clicked(false);
        }
    }

    function no() {
        if(state == "verify") {
            removeNoButton.clicked(false);
        }
    }

    // Restrict mouse events to children
    MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

    color: Qt.rgba(0.1,0.1,0.1,0.8)

    Component.onCompleted: {
        dialog.activate.connect(function() {
            var targets = milky.getTargetPackages();
            if(targets.length == 1) {
                state = "verify";
                removeVerify.removedPackage = targets[0].title;
            } else {
                milky.clearTargets();
                dialog.deactivate();
            }
        });

        milky.events.removeCheck.connect(function() {
            milky.answer(true);
        });
        milky.events.removeStart.connect(function() {
            state = "apply";
        });
        milky.events.removeDone.connect(function() {
            state = "done";
        });

    }

    states: [
        State {
            name: "verify"
            PropertyChanges { target: removeVerify; opacity: 1.0 }
            PropertyChanges { target: removeApply; opacity: 0.0 }
            PropertyChanges { target: removeDone; opacity: 0.0 }
        },
        State {
            name: "apply"
            PropertyChanges { target: removeVerify; opacity: 0.0 }
            PropertyChanges { target: removeApply; opacity: 1.0 }
            PropertyChanges { target: removeDone; opacity: 0.0 }
        },
        State {
            name: "done"
            PropertyChanges { target: removeVerify; opacity: 0.0 }
            PropertyChanges { target: removeApply; opacity: 0.0 }
            PropertyChanges { target: removeDone; opacity: 1.0 }
        }
    ]

    state: "verify"

    Item {
        id: removeVerify
        anchors.centerIn: parent
        height: childrenRect.height
        property string removedPackage: ""

        Text {
            id: removeVerifyLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Remove PND " + parent.removedPackage + "?"
            font.pixelSize: 24
            color: "#eee"
        }
        Button {
            id: removeNoButton
            anchors.top: removeVerifyLabel.bottom
            anchors.right: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#ecc"
            label: "No"
            controlHint: "X"
            onClicked: {
                dialog.deactivate();
                milky.clearTargets();
            }
        }
        Button {
            id: removeYesButton
            anchors.top: removeVerifyLabel.bottom
            anchors.left: parent.horizontalCenter
            anchors.margins: 16
            width: 128
            height: 48
            color: "#cec"
            label: "Yes"
            controlHint: "B"
            onClicked: {
                dialog.milky.remove()
            }
        }

    }

    Item {
        id: removeApply
        anchors.centerIn: parent
        height: childrenRect.height

        Text {
            id: removeProgressLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Removing..."
            font.pixelSize: 24
            color: "#eee"
        }
    }

    Item {
        id: removeDone
        anchors.centerIn: parent
        height: childrenRect.height

        Text {
            id: removeDoneLabel
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Remove complete"
            font.pixelSize: 24
            color: "#eee"
        }
        Button {
            id: removeDoneButton
            anchors.top: removeDoneLabel.bottom
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
