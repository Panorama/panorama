import Qt 4.6
import Panorama 1.0

PanoramaUI {
    id: ui
    name: "Magma"
    description: "An UI that will burn your fingers"
    author: "dflemstr"
    settingsSection: "magma"

    property int level: 0

    Rectangle {
        z: -2
        anchors.fill: parent
        color: "#000022"
    }

    Item {
        id: background
        z: -1
        width: parent.width
        height: parent.height * 3
        Timer {
            interval: 200
            running: level == 0
            repeat: true
            onTriggered: {
                flow.burst(5);
                ash.burst(2);
            }
        }
        Particles {
            id: flow
            x: ui.width / 2
            y: ui.height * 0.65
            width: ui.width / 3
            height: 10
            source: "particles/flow.png"
            lifeSpan: 7000
            lifeSpanDeviation: 100
            count: 0
            angle: 280
            angleDeviation: 50
            velocity: 70
            velocityDeviation: 20
            ParticleMotionGravity {
                xattractor: ui.width
                yattractor: ui.height
                acceleration: 15
            }
        }
        Particles {
            id: ash
            z: -1
            anchors.centerIn: flow
            width: ui.width / 3
            height: 10
            source: "particles/ash.png"
            lifeSpan: 3000
            count: 0
            angle: 270
            angleDeviation: 50
            velocity: 70
            velocityDeviation: 10
            ParticleMotionGravity {
                xattractor: ui.width
                yattractor: ui.height
                acceleration: 7
            }
        }
        Image {
            width: ui.width
            height: ui.height
            z: 1
            source: "overlays/mask.png"
        }
    }

    FocusScope {
        id: level0
        focus: level == 0
        anchors.top: background.top
        width: parent.width
        height: parent.height
        Text {
            text: "My Pandora"
            color: "#000044"
            font.pixelSize: ui.height / 6
        }
    }
    FocusScope {
        id: level1
        focus: level == 1
        anchors.top: level0.bottom
        width: parent.width
        height: parent.height
    }
    FocusScope {
        id: level2
        focus: level == 2
        anchors.top: level1.bottom
        width: parent.width
        height: parent.height
    }

    states: [
        State {
            name: "level0"
            when: ui.level == 0
            PropertyChanges {
                target: background
                x: 0
            }
        },
        State {
            name: "level1"
            when: ui.level == 1
            PropertyChanges {
                target: background
                x: -ui.height / 3
            }
        },
        State {
            name: "level2"
            when: ui.level == 1
            PropertyChanges {
                target: background
                x: -ui.height * 2 / 3
            }
        }
    ]
}
