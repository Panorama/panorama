import Qt 4.7

Item {
    id: button
    property color color: "grey"
    property string label: "Button!"
    property bool toggleButton: false
    property bool pressed: false
    property alias font: labelText.font
    property alias textColor: labelText.color
    property alias enabled: mouseArea.enabled
    property alias radius: rectangle.radius
    property alias border: rectangle.border

    function isDown() {
        return button.pressed || mouseArea.pressed;
    }

    signal clicked(bool pressed);

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

        Text {
            id: labelText
            anchors.centerIn: parent
            font.pixelSize: 18
            text: button.label

        }

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                if(button.toggleButton) {
                    button.pressed = !button.pressed;
                }

                button.clicked(button.pressed)
            }
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

