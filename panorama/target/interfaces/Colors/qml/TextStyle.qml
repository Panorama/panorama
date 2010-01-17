import Qt 4.6

Item {
    id: root
    function accessor(x) {print("not implemented");return null;}

    function getField(x) {
        if("color" == x)
            return color;
        else if("highlightColor" == x)
            return highlightColor;
        else if("bold" == x)
            return bold;
        else if("italic" == x)
            return italic;
        else if("pixelSize" == x)
            return pixelSize;
        else if("family" == x)
            return family;
        else {
            print("Warning: TextStyle does not contain field \"" + x + "\"");
            return null;
        }
    }
    property bool fontify: false
    property bool highlightify: true

    property color color: root.accessor("_color")
    property color highlightColor: highlighify ? root.accessor("_color_highlight") : color
    property int s: accessor("_style")
    property bool bold: (s & 1) == 1
    property bool italic: (s & 2) == 2
    property real pixelSize: root.accessor("_size")
    FontLoader {
        id: loader
        source: "../" + root.accessor(fontify ? "_font" : "")
    }
    property string family: loader.name
}
