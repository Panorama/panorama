import Qt 4.7

Item {
    id: book
    default property alias content: itemModel.children

    property alias background: back.source

    property alias cacheBuffer: pager.cacheBuffer
    property alias count: pager.count
    property alias currentIndex: pager.currentIndex
    property alias currentItem: pager.currentItem

    signal currentIndexChanged

    Keys.onPressed: {
        if(event.key == Qt.Key_Right) {
            pager.incrementCurrentIndex();
            event.accepted = true;
        } else if(event.key == Qt.Key_Left) {
            pager.decrementCurrentIndex();
            event.accepted = true;
        }
    }

    Image {
        id: back
        fillMode: Image.TileHorizontally
        height: parent.height
        x: -(pager.viewportX/pager.viewportWidth) * (back.width-pager.width)
    }
    ListView {
        id: pager
        anchors.fill: parent

        orientation: ListView.Horizontal
        //overShoot: false
        snapMode: ListView.SnapOneItem
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveSpeed: parent.width * 4

        onCurrentIndexChanged: book.currentIndexChanged();

        model: VisualItemModel {
            id: itemModel
        }
    }
}
