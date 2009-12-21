import Qt 4.6

Item {
    id: root
    property string baseName
    property string sourceData: skinCfg.data

    property bool bold: false
    property bool italic: false
    property real pixelSize: 12
    property string family: ""
    property color color: "white"
    property color highlightColor: "white"

    property real intensity: 0

    Script {
        source: "text.js"
    }
    x: readField(sourceData, baseName + "_icon_x") - width / 2
    y: readField(sourceData, baseName + "_icon_y") - height / 2
    Image {
        id: icon
        source: readField(baseName + "_icon")
        x: 0
        y: 0
        opacity: 1 - intensity
    }
    Text {
        anchors.top: icon.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: parent.horizontalCenter
        text: readField(baseName + "_title")
        color: (intensity > 0.5) ? root.highlightColor : root.color
        font.bold: root.bold
        font.italic: root.italic
        font.pixelSize: root.pixelSize
        font.family: root.family
    }
    Image {
        id: iconHighlight
        source: readField(baseName + "_icon_highlight")
        x: 0
        y: 0
        opacity: intensity
    }
}
