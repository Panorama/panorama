import Qt 4.6

Item {
    id: progressbar
    property int minimum: 0
    property int maximum: 100
    property int value: 0
    property alias color: g1.color
    property alias secondColor: g2.color
    property alias textColor: label.color
    property alias style: label.style
    property alias styleColor: label.styleColor
    property bool displayInPercent: false
    property string unit: ""
    
    property real ratio: (value - minimum) / (maximum - minimum)

    height: 48

    Rectangle {
        id: fill
        property alias h: progressbar.height
        property alias w: progressbar.width
        property alias r: progressbar.ratio
        property real b1: ((r - 1) * (Math.PI - 4) * h / 2 + 2 * r * w) / 2
        property real b2: Math.sqrt((r * h / 2 * ((Math.PI - 4) * h / 2 + 2 * w)) / Math.PI) * 2
        property real b: (b2 > h) ? b1 : b2
        b: Behavior { NumberAnimation { duration: 300; easing: "OutQuad" } }
        
        radius: Math.min(b2, h / 2)
        width: b
        height: Math.min(b, h)
        
        smooth: true
        anchors.verticalCenter: parent.verticalCenter
        gradient: Gradient {
            GradientStop {
                id: g1
                position: 0.0
            }
            GradientStop {
                id: g2
                position: 1.0
            }
        }
    }
    Rectangle {
        anchors.fill: parent
        radius: progressbar.height / 2
        smooth: true
        color: "transparent"
        border.color: progressbar.color
        border.width: 2
    }
    Text {
        id: label
        x: 6
        color: "white"
        font.bold: true
        font.pixelSize: progressbar.height * 0.8
        text: (displayInPercent ? (progressbar.ratio * 100).toFixed(2)
            : value + "/" + maximum + " ") + unit
    }
}
