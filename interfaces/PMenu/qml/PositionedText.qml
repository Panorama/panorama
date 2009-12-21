import Qt 4.6

Text {
    id: root
    property string baseName
    property string sourceData: skinCfg.data

    property bool bold: false
    property bool italic: false
    property real pixelSize: 12
    property string family: ""
    property color color: "white"
    property color highlightColor: "white"

    Script {
        source: "text.js"
    }
    x: readField(sourceData, baseName + "_x")
    y: readField(sourceData, baseName + "_y")
    color: root.color
    font.bold: root.bold
    font.italic: root.italic
    font.pixelSize: root.pixelSize
    font.family: root.family
}
