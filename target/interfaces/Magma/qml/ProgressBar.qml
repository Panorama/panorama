import Qt 4.6

Item {
    id: progressbar
    property int minimum: 0
    property int maximum: 100
    property int value: 0
    property alias color: g1.color
    property alias secondColor: g2.color
    property string unit: "%"
    
    height: 24
    clip: true
    
    Rectangle {
        id: fill
        width: EaseFollow {
            source: progressbar.width * (value - minimum) / (maximum-minimum)
            velocity: 1200
        }
        height: parent.height
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
        radius: 5
        color: "transparent"
        border.color: "white"
        border.width: 2
    }
    Text {
        x: 6
        color: "white"
        font.bold: true
        font.pixelSize: progressbar.height * 0.8
        text: value + "/" + maximum + " " + unit
    }
}
