import Qt 4.6

Text {
    id: root
    //Abstract:
    function accessor(x) {print("not implemented");return null;}
    function styleField(x) {print("not implemented");return null;}

    x: accessor("_x")
    y: accessor("_y")
    color: styleField("color")
    font.bold: styleField("bold")
    font.italic: styleField("italic")
    font.pixelSize: styleField("pixelSize")
    font.family: styleField("family")
}
