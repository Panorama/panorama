import Qt 4.6
import Panorama 1.0

PanoramaUI {
    id: ui
    name: "Magma"
    description: "An UI that will burn your fingers"
    author: "dflemstr"
    settingsSection: "magma"

    property int level: 0
    property string topSection: ""

    Rectangle {
        z: -2
        anchors.fill: parent
        color: "#000022"
    }

    SystemInformation {
        id: sysinfo
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
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: "My Pandora"
            color: "#000044"
            font.pixelSize: ui.height / 6
        }
        Column {
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: ui.height / 4
            anchors.leftMargin: 10
            Text {
                color: "#111111"
                font.pixelSize: ui.height / 16
                text: "<table><tr><td>RAM:</td><td>" + sysinfo.usedRam + "</td>" +
                    "<td>/</td><td>" + sysinfo.ram + "</td><td>MiB</td></tr>" +
                    "<tr><td>Swap:</td><td>" + sysinfo.usedSwap + "</td>" +
                    "<td>/</td><td>" + sysinfo.swap + "</td><td>MiB</td></tr></table>"
            }
        }
        ListModel {
            id: menu
            ListElement {
                title: "Applications"
                section: "apps"
            }
            ListElement {
                title: "Favorites"
                section: "favs"
            }
            ListElement {
                title: "Settings"
                section: "setts"
            }
        }
        Script {
            function setSection(section) {
                topSection = section;
                level = 1;
            }
        }
        ListView {
            id: topMenu
            focus: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: ui.height / 32
            anchors.horizontalCenter: parent.horizontalCenter
            height: ui.height / 16
            width: parent.width - 20
            orientation: ListView.Horizontal
            model: menu
            overShoot: false
            Keys.onDigit1Pressed: {
                setSection(topMenu.currentItem.section);
            }
            delegate: Text {
                text: title + " "
                font.pixelSize: ui.height / 16
                color: "#111111"
                effect: DropShadow {
                    xOffset: 0
                    yOffset: 0
                    color: "#333333"
                    blurRadius: EaseFollow {
                        source: ListView.isCurrentItem ? 8 : 0
                        velocity: 50
                    }
                }
                MouseRegion {
                    anchors.fill: parent
                    onClicked: {
                        setSection(section);
                    }
                }
            }
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
                y: 0
            }
        },
        State {
            name: "level1"
            when: ui.level == 1
            PropertyChanges {
                target: background
                y: -ui.height
            }
        },
        State {
            name: "level2"
            when: ui.level == 1
            PropertyChanges {
                target: background
                y: -ui.height * 2
            }
        }
    ]
    transitions: [
        Transition {
            NumberAnimation {
                matchProperties: "y"
                duration: 500
                easing: "easeInOutQuart"
            }
        }
    ]
}
