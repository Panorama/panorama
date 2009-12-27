import Qt 4.6
import Panorama 1.0

Item {
    id: apps
    signal selected(string id)
    signal favStarClicked(string id)
    property real itemHeight: parent.height / 10
    property real itemWidth: parent.width / 3 - 10
    property alias model: appView.model
    property alias currentItem: appView.currentItem
    
    Keys.onDigit1Pressed: {
        selected(appView.currentItem.ident);
    }
    Keys.onSpacePressed: {
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
            MouseRegion {
                id: delegMouse
                anchors.fill: parent
                onClicked: {
                    appView.currentIndex = index;
                    selected(identifier);
                }
            }
            Image {
                anchors.top: parent.top
                anchors.right: parent.right
                source: favorites.value.indexOf(identifier) == -1 ? "../images/favorite-disabled.png" : "../images/favorite-enabled.png"
            }
            Row {
                width: apps.itemWidth
                height: apps.itemHeight
                Image {
                    id: iconField
                    source: icon
                    smooth: true
                    width: apps.itemHeight
                    height: apps.itemHeight
                }
                Column {
                    width: parent.width - iconField.height - 5
                    height: parent.height
                    Text {
                        id: nameLabel
                        text: name
                        width: parent.width
                        anchors.top: parent.top
                        font.pixelSize: apps.itemHeight / 3
                        color: "white"
                        elide: Text.ElideRight
                        font.bold: true
                    }
                    Text {
                        text: comment
                        width: parent.width
                        anchors.top: nameLabel.bottom
                        anchors.bottom: parent.bottom
                        font.pixelSize: apps.itemHeight / 5
                        color: "white"
                        wrap: true
                    }
                }
            }
        }
    }
    Component {
        id: highl
        Rectangle {
            color: "gray"
            opacity: 0.5
            radius: apps.itemHeight / 8
            width: apps.itemWidth
            height: apps.itemHeight
            x: SpringFollow {
                source: appView.currentItem.x
                spring: 3
                damping: 0.2
            }
            y: SpringFollow {
                source: appView.currentItem.y
                spring: 3
                damping: 0.2
            }
        }
    }
    GridView {
        id: appView
        focus: true
        anchors.fill: parent
        cellWidth: apps.itemWidth
        cellHeight: apps.itemHeight
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
