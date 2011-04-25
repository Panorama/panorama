import Qt 4.7

Item {
    id: root
    property color highlightColor: "steelblue"
    property color textColor: "white"
    property real itemHeight: 32
    property alias categoryFilter: catSelector.selectedCategory
    property alias nameFilter: nameField.text
    property alias appSource: appView.model
    signal selected(string identifier)

    Keys.onDownPressed: {
        appView.incrementCurrentIndex();
    }

    Keys.onUpPressed: {
        appView.decrementCurrentIndex();
    }

    Component {
        id: appDelegate
        Item {
            id: wrapper
            property string ident: identifier
            width: appView.width
            height: itemHeight
            
            MouseArea {
                id: delegMouse
                anchors.fill: parent
                onClicked: {
                    appView.currentIndex = index;
                }
                onDoubleClicked: {
                    selected(appView.currentItem.ident);
                }
            }
            Row {
                height: root.itemHeight
                width :parent.width
                Image {
                    id: iconField
                    source: icon
                    smooth: true
                    x: 0
                    y: 0
                    width: root.itemHeight
                    height: root.itemHeight
                }
                Column {
                    x: parent.height + 5
                    y: 0
                    width: parent.width - parent.height - 5
                    height: parent.height
                    Text {
                        text: name
                        width: parent.width
                        font.pixelSize: root.itemHeight * 0.5
                        color: root.textColor
                        elide: Text.ElideRight
                        font.bold: true
                    }
                    Text {
                        text: comment
                        width: parent.width
                        font.pixelSize: root.itemHeight * 0.3
                        color: root.textColor
                        elide: Text.ElideRight
                    }
                }
            }
        }
    }
    Component {
        id: highl
        Rectangle {
            color: root.highlightColor
            opacity: 0.5
            radius: root.itemHeight / 8
            width: appView.width
            x: 0
            Behavior on y { 
                SpringAnimation { 
                    spring: 2 
                    damping: 0.2 
                }                 
            }
        }
    }

    Item {
        id: filters
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.topMargin: 3
        anchors.bottomMargin: 3
        width: 200
        //spacing: 5
        z: 2
        Text {
            id: nameText
            text: "Name"
            font.pixelSize: root.itemHeight * 0.7
            color: root.textColor
            anchors.top: parent.top
        }
        TextInput {
            id: nameField
            anchors.top: nameText.bottom
            anchors.topMargin: 5
            width: parent.width
            height: root.itemHeight * 0.7
            color: root.textColor
            font.pixelSize: height * 0.8
            focus: true
            Keys.onEnterPressed: selected(appView.currentItem.ident);
            Keys.onReturnPressed: selected(appView.currentItem.ident);
            Rectangle {
                anchors.fill: parent
                anchors.leftMargin: -3
                anchors.rightMargin: -3
                anchors.topMargin: -3
                anchors.bottomMargin: -3
                color: root.textColor
                radius: 3
                opacity :0.5
            }
        }
        Text {
            id: catText
            text: "Category"
            font.pixelSize: root.itemHeight * 0.7
            color: root.textColor
            anchors.top: nameField.bottom
            anchors.topMargin: 5
        }
        ListView {
            id: catSelector
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: catText.bottom
            anchors.topMargin: 5
            anchors.bottom: parent.bottom
            property string selectedCategory: ""
            onCurrentIndexChanged: {
                selectedCategory = currentItem.rawName
            }
            Rectangle {
                z: -1
                anchors.fill: parent
                anchors.leftMargin: -3
                anchors.rightMargin: -3
                anchors.topMargin: -3
                anchors.bottomMargin: -3
                color: root.textColor
                radius: 3
                opacity :0.5
            }
            model: ListModel {
                ListElement {
                    name: "All"
                    raw: ".*"
                }
                ListElement {
                    name: "Accessories"
                    raw: "Utility"
                }
                ListElement {
                    name: "Games"
                    raw: "Game"
                }
                ListElement {
                    name: "Graphics"
                    raw: "Graphics"
                }
                ListElement {
                    name: "Internet"
                    raw: "Network"
                }
                ListElement {
                    name: "Office"
                    raw: "Office"
                }
                ListElement {
                    name: "Programming"
                    raw: "Development"
                }
                ListElement {
                    name: "Sound & Video"
                    raw: "AudioVideo|Audio|Video"
                }
                ListElement {
                    name: "System Tools"
                    raw: "System"
                }
                ListElement {
                    name: "Category-less"
                    raw: "NoCategory"
                }
            }
            delegate: Item {
                property string rawName: raw
                height: root.itemHeight * 0.7
                width: catSelector.width
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        catSelector.currentIndex = index;
                    }
                }
                Text {
                    text: name
                    width: parent.width
                    anchors.leftMargin: 3
                    font.pixelSize: root.itemHeight * 0.6
                    color: root.textColor
                    elide: Text.ElideRight
                    font.bold: true
                }
            }
            highlight: Rectangle {
                color: root.highlightColor
                opacity: 0.5
                radius: root.itemHeight / 8
            }
        }
    }

    Item {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.right: filters.left
        anchors.rightMargin: 5
        Rectangle {
            z: -1
            anchors.fill: parent
            color: root.textColor
            radius: 3
            opacity :0.5
        }
        ListView {
            id: appView
            highlight: highl
            snapMode: ListView.SnapOneItem
            //highlightFollowsCurrentItem: false
            clip: true
            delegate: appDelegate
            anchors.fill: parent
            anchors.leftMargin: 3
            anchors.rightMargin: 3
            anchors.topMargin: 3
            anchors.bottomMargin: 3
        }
        Image {
            anchors.right: appView.right; anchors.top: appView.top
            source: "../images/emblems/arrow-up.png"; opacity: appView.atYBeginning ? 0 : 1
        }
        Image {
            anchors.right: appView.right; anchors.bottom: appView.bottom
            source: "../images/emblems/arrow-down.png"; opacity: appView.atYEnd ? 0 : 1
        }

    }
}
