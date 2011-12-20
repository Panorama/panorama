import Qt 4.7

Rectangle {
    id: dialog
    property QtObject categoryFilter
    property alias categoryList: categoryList
    property alias model: categoryList.model

    color: Qt.rgba(0.1,0.1,0.1,0.8)

    // Restrict mouse events to children
    MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

    Row {
        id: orderByButtons
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Repeater {
            id: orderByButtonsRepeater
            model: categoryFilter.orderOptions
            delegate: Button {
                property int ident: index
                label: modelData.title
                color: "#ddd"
                width: orderByButtons.width/(orderByButtonsRepeater.model.length)
                pressed:  categoryFilter.selectedOrder == ident
                controlHint: "Y"
                border {
                    color: "#444"
                    width: 1
                }
                onClicked: {
                    categoryFilter.selectedOrder = ident;
                }
            }
        }
    }

    GridView {
        id: categoryList
        anchors.top: orderByButtons.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true
        cellWidth: width / 4
        cellHeight: 48
        cacheBuffer: height / 2
        currentIndex: 0

        highlightFollowsCurrentItem: false
        highlight: Rectangle {
            color: Qt.rgba(1.0, 1.0, 1.0, 0.2)
            z: 100
            x: categoryList.currentItem.x
            y: categoryList.currentItem.y
            height: categoryList.currentItem.height
            width: categoryList.currentItem.width
            border {
                color: "#dad"
                width: 4
            }
            radius: 4
        }

        delegate: Button {
            width: categoryList.width / 4 - 4
            height: 44
            border {
                color: "#ccc"
                width: 2
            }
            textColor: "#eee"
            font.pixelSize: 18
            color: "#a8a"
            //radius: 4
            label: edit ? edit : "All"
            pressed: categoryFilter.value === edit
            onClicked: {
                categoryFilter.value = edit;
            }
        }
    }
}
