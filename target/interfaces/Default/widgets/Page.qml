import Qt 4.6

Item {
    id: page
    property real topbarHeight: 64
    property color labelColor: "white"
    property color labelShadowColor: "black"
    property color labelOutlineColor: "black"
    property alias icon: icon.source
    property alias title: label.text
    default property alias content: body.children

    Image {
        id: icon
        width: topbarHeight
        height: topbarHeight
        smooth: true
        anchors.left: parent.left
        anchors.top: parent.top
        effect: DropShadow {
            id: imageShadow
            color: page.labelShadowColor
            xOffset: 0
            yOffset: 0
            blurRadius: 5
        }
    }
    Text {
        id: label
        height: topbarHeight
        color: page.labelColor
        verticalAlignment: Text.AlignVCenter
        anchors.top: parent.top
        anchors.left: icon.right
        anchors.leftMargin: page.topbarHeight * 0.2
        font.bold: true
        font.pixelSize: page.topbarHeight * 0.8
        style: Text.Outline
        styleColor: page.labelOutlineColor
        effect: DropShadow {
            id: labelShadow
            color: page.labelShadowColor
            xOffset: 0
            yOffset: 0
            blurRadius: 5
        }
    }
    Item {
        anchors.top: label.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: 5
        anchors.bottomMargin: 5
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        FocusScope {
            id: body
            focus: ListView.isCurrentItem //The isCurrentItem property is defined inside of a ListView
            anchors.fill: parent
        }
    }
}
