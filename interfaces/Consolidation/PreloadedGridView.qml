import QtQuick 1.0

Flickable {
    id: view
    property alias model: repeater.model
    property alias delegate: repeater.delegate
    property Component highlight

    property alias count: repeater.count
    property int currentIndex: 0
    property QtObject currentItem: grid.children[currentIndex] //repeater.itemAt(currentIndex)
    property int cellWidth: 64
    property int cellHeight: 64

    contentWidth: width
    contentHeight: grid.height

    Grid {
        id: grid
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        columns: Math.floor(view.width / view.cellWidth)
        rows: Math.ceil(repeater.count / columns)

        Repeater {
            id: repeater
        }
    }

    Loader {
        sourceComponent: view.highlight
        z: -1
    }

    function moveCurrentIndexUp() {
        if(currentIndex - grid.columns >= 0) {
            currentIndex -= grid.columns;
        }

        if(currentItem.y < contentY) {
            contentY = currentItem.y;
        }

    }

    function moveCurrentIndexDown() {
        var currentRow = Math.floor(currentIndex / grid.columns);
        if(currentIndex + grid.columns < count) {
            currentIndex += grid.columns;
        } else if(currentRow < grid.rows - 1) {
            currentIndex = count - 1;
        }

        if(currentItem.y + currentItem.height > contentY + view.height) {
            contentY = currentItem.y + currentItem.height - view.height;
        }

    }

    function moveCurrentIndexLeft() {
        var rowIndex = currentIndex % grid.columns;
        if(rowIndex !== 0) {
            currentIndex -= 1;
        }
    }

    function moveCurrentIndexRight() {
        var rowIndex = currentIndex % grid.columns;
        var currentRow = Math.floor((currentIndex + 1) / grid.columns);
        var currentRowSize  = currentRow < grid.rows - 1 ? grid.columns : count % grid.columns;

        if(rowIndex < currentRowSize - 1) {
            currentIndex += 1;
        }
    }
}
