import Qt 4.6

Image {
    property string baseName
    property string sourceData: skinCfg.data
    Script {
        source: "text.js"
    }
    x: readField(sourceData, baseName + "_x")
    y: readField(sourceData, baseName + "_y")
}
