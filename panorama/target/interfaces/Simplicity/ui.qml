import Qt 4.7
import Panorama 1.0

PanoramaUI {
    id: ui
    name: "Simplicity"
    description: "A simple theme"
    author: "dflemstr"
    settingsSection: "simplicity"

    Keys.onUpPressed: appView.decrementCurrentIndex()
    Keys.onDownPressed: appView.incrementCurrentIndex()

    SystemInformation { id: sysinfo }

    Image {
        anchors.fill: parent
        source: "images/background.png"
    }

    Row {
        id: bar
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        height: 25
        spacing: 10
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: "RAM"; color: "white"; font.bold: true
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 30; height: 5; border.width: 1; border.color: "white"
            color: "transparent"; clip: true
            Rectangle {
                width: parent.width * (sysinfo.usedRam / sysinfo.ram)
                height: parent.height; color: "white"
            }
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: " SD1"; color: "white"; font.bold: true
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 30; height: 5; border.width: 1; border.color: "white"
            color: "transparent"; clip: true
            Rectangle {
                width: parent.width * (sysinfo.usedSd1 / sysinfo.sd1)
                height: parent.height; color: "white"
            }
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: " SD2"; color: "white"; font.bold: true
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 30; height: 5; border.width: 1; border.color: "white"
            color: "transparent"; clip: true
            Rectangle {
                width: parent.width * (sysinfo.usedSd2 / sysinfo.sd2)
                height: parent.height; color: "white"
            }
        }
        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: " CPU"; color: "white"; font.bold: true
        }
        Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: 30; height: 5; border.width: 1; border.color: "white"
            color: "transparent"; clip: true
            Rectangle {
                width: parent.width * (sysinfo.usedCpu / sysinfo.cpu)
                height: parent.height; color: "white"
            }
        }
    }

    Text {
        anchors.bottom: box.top
        anchors.left: box.left
        anchors.bottomMargin: 3
        text: "Specify an application to launch:"
        color: "#38404D"
    }
    TextInput {
        id: box
        width: parent.width / 2
        anchors.centerIn: parent
        activeFocusOnPress: false
        cursorVisible: container.focus
        Rectangle {
            id: container
            anchors.fill: parent
            anchors.topMargin: -3
            anchors.bottomMargin: -3
            anchors.leftMargin: -8
            anchors.rightMargin: -8
            color: "white"
            opacity: 0.5
            radius: 8
            focus: true
            Keys.onEnterPressed: ui.execute(appView.currentItem.ident)
            Keys.onReturnPressed: ui.execute(appView.currentItem.ident)
        }
    }
    ListView {
        id: appView
        anchors.horizontalCenter: box.horizontalCenter
        anchors.top: box.bottom
        anchors.topMargin: 8
        anchors.bottom: bar.top
        width: parent.width / 2
        //overShoot: false
        clip: true
        model: applications
            .matching("name", box.text.length > 0 ? ".*" + box.text + ".*" : "^$")
            .sortedBy("name", true)
        highlight: Rectangle {
            color: "white"
            opacity: 0.5
            radius: 8
        }
        delegate: Item {
            id: deleg
            property string ident: identifier
            width: appView.width
            height: Math.ceil(appView.height / 4)
            Image {
                id: iconField
                source: icon
                smooth: true
                width: parent.height
                height: parent.height
            }
            Item {
                width: parent.width - iconField.height - 5
                height: parent.height
                anchors.left: iconField.right
                anchors.leftMargin: 5
                Text {
                    id: nameLabel
                    text: name
                    width: parent.width
                    anchors.top: parent.top
                    font.pixelSize: deleg.height / 3
                    color: "#FFA027"
                    elide: Text.ElideRight
                    font.bold: true
                }
                Item {
                    id: commentContainer
                    width: parent.width
                    anchors.top: nameLabel.bottom
                    anchors.bottom: parent.bottom
                    clip: true
                    Text {
                        id: commentLabel
                        text: comment
                        width: parent.width
                        font.pixelSize: deleg.height / 5
                        color: "#38404D"
                        wrapMode: Text.Wrap
                        Behavior on y {
                            SequentialAnimation {
                                running: ListView.isCurrentItem
                                //repeat: true
                                PauseAnimation {
                                    duration: 1000
                                }
                                NumberAnimation {
                                    from: 0
                                    to: Math.min(0, commentContainer.height - commentLabel.height)
                                    duration: 1000
                                }
                                PauseAnimation {
                                    duration: 1000
                                }
                                NumberAnimation { to: 0; duration: 100 }
                            }
                        }
                    }
                }
            }
            MouseArea {
                anchors.fill: parent
                onClicked: appView.currentIndex = index
            }
        }
    }
}
