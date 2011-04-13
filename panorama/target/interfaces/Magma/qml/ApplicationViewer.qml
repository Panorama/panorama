import Qt 4.7
import Panorama 1.0

Item {
    id: apps
    signal selected(string id)
    signal pressed2()
    signal pressed3()
    signal pressed4()
    signal favStarClicked(string id)
    property real itemHeight: parent.height / 10
    property real itemWidth: parent.width / 3 - 10
    property alias model: appView.model
    property alias currentItem: appView.currentItem
    property alias nameFilter: nameField.text

    Keys.onEnterPressed: {
        selected(appView.currentItem.ident);
    }
    Keys.onReturnPressed: {
        selected(appView.currentItem.ident);
    }

    Setting {
        id: favorites
        section: "system"
        key: "favorites"
    }

    Component {
        id: appDelegate
        Item {
            id: wrapper
            property string ident: identifier
            width: apps.itemWidth
            height: apps.itemHeight
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    appView.currentIndex = index;
                    selected(identifier);
                }
            }
            Image {
                id: favIcon
                anchors.top: parent.top
                anchors.right: parent.right
                source: favorites.value.indexOf(identifier) == -1 ? "../images/favorite-disabled.png" : "../images/favorite-enabled.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        favStarClicked(identifier);
                    }
                }
            }
            Row {
                anchors.fill: parent
                Image {
                    id: iconField
                    source: icon
                    smooth: true
                    width: apps.itemHeight
                    height: apps.itemHeight
                }
                Item { //separator
                    width: 5
                    height: parent.height
                }
                Item {
                    width: parent.width - iconField.height - 5
                    height: parent.height
                    Text {
                        id: nameLabel
                        text: name
                        width: parent.width - favIcon.width
                        anchors.top: parent.top
                        font.pixelSize: apps.itemHeight / 3
                        color: "#f7c767"
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
                            font.pixelSize: apps.itemHeight / 5
                            color: "#ed8d06"
                            wrapMode: Text.Wrap
                            Behavior on y {
                                SequentialAnimation {
                                    running: true
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
            }
        }
    }
    Component {
        id: highl
        Rectangle {
            color: "#C96823"
            opacity: 0.5
            radius: apps.itemHeight / 8
            width: apps.itemWidth
            height: apps.itemHeight
            x: appView.currentItem.x
            Behavior on x {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
            y: appView.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }
    Keys.onUpPressed: {
        appView.moveCurrentIndexUp();
    }
    Keys.onDownPressed: {
        appView.moveCurrentIndexDown();
    }
    Keys.onLeftPressed: {
        appView.moveCurrentIndexLeft();
    }
    Keys.onRightPressed: {
        appView.moveCurrentIndexRight();
    }
    Item {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: -32
        anchors.rightMargin: 8
        width: parent.width * 0.3
        height: apps.itemHeight / 3
        z: 6
        opacity: nameField.text.length > 0 ? 1 : 0
        Behavior on opacity {
            NumberAnimation {
                duration: 500
            }
        }
        Rectangle {
            anchors.fill: parent
            anchors.leftMargin: -3
            anchors.rightMargin: -3
            anchors.topMargin: -3
            anchors.bottomMargin: -3
            z: -1
            color: "#900000"
            radius: 3
        }
        Text {
            id: nameText
            text: "Name: "
            color: "white"
            height: parent.height
            font.pixelSize: Math.max(1, parent.height)
            font.bold: true
        }
        TextInput {
            id: nameField
            anchors.left: nameText.right
            anchors.right: parent.right
            height: parent.height
            color: "white"
            font.pixelSize: Math.max(1, parent.height)
            activeFocusOnPress: false
            cursorVisible: keyInterceptor.focus
            Item {
                id: keyInterceptor
                focus: true
                //Hack so that we can intercept the "1" keypress before the TextInput grabs it
                Keys.onDigit1Pressed: selected(appView.currentItem.ident);
                Keys.onDigit2Pressed: pressed2();
                Keys.onDigit3Pressed: pressed3();
                Keys.onDigit4Pressed: pressed4();
            }
        }
    }
    GridView {
        id: appView
        cellWidth: apps.itemWidth + 5 //for some spacing
        cellHeight: apps.itemHeight + 5
        highlight: highl
        highlightFollowsCurrentItem: false
        delegate: appDelegate
        anchors.fill: parent
        anchors.leftMargin: 3
        anchors.rightMargin: 3
        anchors.topMargin: 3
        anchors.bottomMargin: 3
    }
}
