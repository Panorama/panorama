import Qt 4.6

Item {
    id: root
    //Abstract:
    function accessor(x) {print("not implemented");return null;}
    function styleField(x) {print("not implemented");return null;}

    x: accessor("_x")
    y: accessor("_y")
    property alias text: textView.text

    Item {
        id: attachment
        x: 0
        y: 10 //For some reason, PMenu displaces these
    }

    Text {
        id: textView
        anchors.baseline: attachment.top
        color: styleField("color")
        font.bold: styleField("bold")
        font.italic: styleField("italic")
        font.pixelSize: styleField("pixelSize")
        font.family: styleField("family")
    }
}
