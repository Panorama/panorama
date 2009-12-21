import Qt 4.6

Item {
    id: root
    //Abstract:
    function accessor(x) {print("not implemented");return null;}
    function styleField(x) {print("not implemented");return null;}

    signal clicked()

    property real intensity: 0

    x: accessor("_icon_x")
    y: accessor("_icon_y")
    Image {
        id: icon
        source: "../" + accessor("_icon")
        x: -width / 2
        y: -height / 2
        opacity: 1 - intensity
        MouseRegion {
            anchors.fill: parent
            onClicked: root.clicked()
        }
    }
    Text {
        anchors.top: icon.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: parent.horizontalCenter
        text: accessor("_title")
        color: (intensity > 0.5) ? styleField("highlightColor") : styleField("color")
        font.bold: styleField("bold")
        font.italic: styleField("italic")
        font.pixelSize: styleField("pixelSize")
        font.family: styleField("family")
        MouseRegion {
            anchors.fill: parent
            onClicked: root.clicked()
        }
    }
    Image {
        id: iconHighlight
        source: "../" + accessor("_icon_highlight")
        x: -width / 2
        y: -height / 2
        opacity: intensity
    }
}
