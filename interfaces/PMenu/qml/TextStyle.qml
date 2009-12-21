import Qt 4.6

Item {
    property string baseName
    property string sourceData: skinCfg.data
    property alias font: proto.font
    property color color: readField(sourceData, baseName + "_color")
    property color highlightColor: sourceData.indexOf(baseName + "_color_highlight") >= 0 ?
        readField(sourceData, baseName + "_color_highlight")
        : color
    Script {
        source: "text.js"
    }
    Text { //prototype
        id: proto
        font.bold: bold
        property int s: readField(sourceData, baseName + "_style")
        property bool bold: (s & 1) == 1
        font.italic: italic
        property bool italic: (s & 2) == 2
        font.pixelSize: readField(sourceData, baseName + "_size")
        font.family: loadFont(readField(sourceData, baseName), bold, italic)
    }
}
