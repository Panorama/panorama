import Qt 4.7

Item {
    id: button
    property color color: "lightgrey"
    property string label: "Button!"
    property bool toggleButton: false
    property bool pressed: false
    property alias font: labelText.font
    property alias textColor: labelText.color
    property alias enabled: mouseArea.enabled
    property alias radius: rectangle.radius
    property alias border: rectangle.border
    property alias controlHint: controlHintText.text

    function isDown() {
        return button.pressed || mouseArea.pressed;
    }

    signal clicked();

    onClicked: {
        if(button.toggleButton) {
            button.pressed = !button.pressed;
        }
    }

    width: 64
    height: 32

    Rectangle {
        id: rectangle
        anchors.fill: parent

        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.darker(button.color, button.isDown() ? 1.6 : 1.0 ) }
            GradientStop { position: button.isDown() ? 0.2 : 0.8; color: Qt.darker(button.color, button.isDown() ? 1.4 : 1.2) }
            GradientStop { position: 1.0; color: Qt.darker(button.color, button.isDown() ? 1.2 : 1.4) }
        }

        clip: true

        Row {
            anchors.centerIn: parent
            width: childrenRect.width
            height: parent.height
            spacing: 4
            Rectangle {
                id: controlHintCircle
                anchors.verticalCenter: parent.verticalCenter
                height: 16
                width: height
                radius: height/2
                color: "transparent"
                visible: controlHintText.text != ""
                border {
                    width: 1
                    color: controlHintText.color
                }

                Text {
                    id: controlHintText
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset: 1
                    text: ""
                    font.pixelSize: 12
                    color: "#333"
                }
            }

            Text {
                id: labelText
                font.pixelSize: 18
                text: button.label
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: button.clicked()
        }

        Rectangle {
            width: parent.height
            height: 8
            visible: button.isDown()
            transformOrigin: Rectangle.Bottom
            anchors.bottom: parent.verticalCenter
            anchors.horizontalCenter: parent.left
            rotation: 90

            gradient: Gradient {
                GradientStop { position: 0; color: Qt.rgba(0,0,0,0) }
                GradientStop { position: 1; color: Qt.rgba(0,0,0,0.2) }
            }
        }
        Rectangle {
            width: parent.height
            height: 8
            visible: button.isDown()
            transformOrigin: Rectangle.Bottom
            anchors.bottom: parent.verticalCenter
            anchors.horizontalCenter: parent.right
            rotation: -90

            gradient: Gradient {
                GradientStop { position: 0; color: Qt.rgba(0,0,0,0) }
                GradientStop { position: 1; color: Qt.rgba(0,0,0,0.2) }
            }
        }
    }

}

