import Qt 4.7                   //Import Qt
import Panorama.Settings 1.0
import Panorama.UI 1.0
import Panorama.Pandora 1.0
import Panorama.Applications 1.0

PanoramaUI {
    id: ui
    name: "Tabbed"
    description: "A tab based UI"
    author: "B-ZaR"
    anchors.fill: parent

    Setting {
        id: minimumNumberOfColumns
        section: "Tabbed"
        key: "minimumNumberOfColumns"
        defaultValue: 8
    }

    Setting {
        id: maximumIconSize
        section: "Tabbed"
        key: "maximumIconSize"
        defaultValue: 96
    }

    Setting {
        id: iconSpacing
        section: "Tabbed"
        key: "iconSpacing"
        defaultValue: 8
    }

    Item {
        id: keyHandler
        focus: true
        Keys.forwardTo: [applications, tabs, search]
    }

    Rectangle {
        id: header
        z: 1
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 32

        color: "#222"

        Rectangle {
            id: searchBox
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.topMargin: 8
            anchors.bottomMargin: 8
            anchors.leftMargin: 4
            color: "white"
            width: 200
            radius: 8

            Row {
                anchors.fill: parent
                Image {
                    source: "images/search.png"
                    height: parent.height
                    width: parent.height
                    smooth: true
                }
                TextInput {
                    id: search
                    activeFocusOnPress: false
                    cursorVisible: false
                    width: parent.width - parent.height
                }
            }
        }
        Text {
            id: clock
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.rightMargin: 4

            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 24
            color: "#eee"

            function zeroPad(integer, size) {
                var s = integer.toString()
                if(s.length < size) {
                    for(var i = s.length; i < size; ++i) {
                        s = "0" + s;
                    }
                }
                return s;
            }

            function weekDayString(weekDayNumber) {
                var weekdays = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
                return weekdays[weekDayNumber];
            }

            text: weekDayString(time.weekday) + " " + time.year + "-" + zeroPad(time.month, 2) + "-" + zeroPad(time.day, 2) + " " + zeroPad(time.hour, 2) + ":" + zeroPad(time.minute, 2)

            Timer {
                id: time
                property int year
                property int month
                property int day
                property int weekday
                property int hour
                property int minute

                interval: 1000
                running: true
                repeat: true
                triggeredOnStart: true
                onTriggered: {
                    var date = new Date;
                    year = date.getFullYear();
                    month = date.getMonth();
                    day = date.getDate();
                    weekday = date.getDay();
                    hour = date.getHours();
                    minute = date.getMinutes();
                }
            }
        }
    }

    Rectangle {
        id: tabs
        color: "#222"
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 170

        function selectedTab() {
            // A hack to compensate for Repeater's weird behavior. For some reason Repeater can be either the first or last child
            // of its parent after loading, but is somewhere in between immediately after creating the elements.
            // The below hack takes into account all of the cases assuming the first child is wanted at load time
            return tabColumn.children[0].fullName !== undefined ? tabColumn.children[selected] : tabColumn.children[selected+1];
        }

        property int selected: 0
        property string selectedName: selectedTab().fullName ? selectedTab().fullName : "Error"
        property string selectedRawName: selectedTab().rawName ? selectedTab().rawName : "None"

        function nextTab() {
            selected = (selected+1) % tabModel.count;
            applications.currentIndex = 0;
        }

        function prevTab() {
            selected = (selected > 0) ? (selected - 1) : tabModel.count - 1;
            applications.currentIndex = 0;
        }

        Keys.onPressed: {
            if(Pandora.controlsActive)
                return;
            if(event.key == Qt.Key_PageUp) {
                prevTab();
                event.accepted = true;
            } else if(event.key == Qt.Key_PageDown) {
                nextTab();
                event.accepted = true;
            }
        }

        Pandora.onPressed: {
            if(event.key == Pandora.TriggerL) {
                prevTab();
                event.accepted = true;
            } else if(event.key == Pandora.TriggerR) {
                nextTab();
                event.accepted = true;
            }
        }
        Column {
            id: tabColumn

            anchors.fill: parent
            anchors.topMargin: (parent.height % 10) / 2
            anchors.bottomMargin: (parent.height % 10) / 2

            Repeater {
                model: ListModel {
                    id: tabModel
                    ListElement { name: "All"; raw: ".*" }
                    ListElement { name: "Accessories"; raw: "Utility" }
                    ListElement { name: "Games"; raw: "Game"}
                    ListElement { name: "Graphics"; raw: "Graphics" }
                    ListElement { name: "Internet"; raw: "Network" }
                    ListElement { name: "Office"; raw: "Office" }
                    ListElement { name: "Programming"; raw: "Development" }
                    ListElement { name: "Media"; raw: "AudioVideo|Audio|Video" }
                    ListElement { name: "System"; raw: "System" }
                    ListElement { name: "Other"; raw: "NoCategory" }
                }
                delegate: Rectangle {
                    property string rawName: raw
                    property string fullName: name

                    property bool selected: tabs.selected == index

                    border {
                        color: "#333"
                        width: 1
                    }
                    height: tabColumn.height/10
                    width: tabColumn.width
                    color: "#444"
                    z: 2

                    Rectangle {
                        anchors.centerIn: parent
                        width:parent.height
                        height:parent.width
                        rotation: 90
                        opacity: parent.selected ? 1.0 : 0.0
                        gradient: Gradient { GradientStop { position: 0.0; color: "#eee" } GradientStop { position: 1.0; color: "#ccc" } }
                    }
                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            tabs.selected = index;
                            applications.currentIndex = 0;
                        }
                    }
                    Text {
                        text: fullName
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        anchors.margins: 2
                        font.pixelSize: parent.width/10
                        color: parent.selected ? "#111" : "#eee"
                        font.bold: true
                    }
                }
            }
        }
    }

    Rectangle {
        id: content
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: tabs.right
        anchors.right: parent.right
        radius: (tabs.height % 10) / 2
        color: "#eee"

        Text {
            text: tabs.selectedName
            font {
                bold: true
                pixelSize: 200
            }
            color: "#ddd"
            anchors.bottom: parent.bottom
        }

        GridView {
            id: applications

            function calculateItemSize() {
                var width = applications.width - 2 * applications.anchors.margins;
                var cols = applications.minNumColumns;
                if(width/cols > applications.maxItemSize) {
                    var cols = Math.ceil(width/applications.maxItemSize);
                }
                return parseInt(width / cols);
            }

            property int maxItemSize: maximumIconSize.value
            property int minNumColumns: minimumNumberOfColumns.value
            property int itemSize: calculateItemSize()
            property int itemSpacing: iconSpacing.value

            cellWidth: itemSize
            cellHeight: itemSize

            highlight: Rectangle { color: "#555"; opacity: 0.5; radius: width/8; width: applications.itemSize; height: applications.itemSize }
            anchors.fill: parent
            anchors.margins: 5

            model: Applications.list.inCategory(tabs.selectedRawName)
                    .matching("name", (search.text.length == 0) ? ".*" : ".*" + search.text + ".*")
                    .sortedBy("name", true)

            // Disable default navigation keys
            Keys.onUpPressed:    {if(!Pandora.controlsActive) event.accepted = false;}
            Keys.onDownPressed:  {if(!Pandora.controlsActive) event.accepted = false;}
            Keys.onLeftPressed:  {if(!Pandora.controlsActive) event.accepted = false;}
            Keys.onRightPressed: {if(!Pandora.controlsActive) event.accepted = false;}

            Keys.onPressed: {
                if(Pandora.controlsActive)
                    return;
                var accept = true;
                switch(event.key) {
                    case Qt.Key_Up:
                        applications.moveCurrentIndexUp();
                        break;
                    case Qt.Key_Down:
                        applications.moveCurrentIndexDown();
                        break;
                    case Qt.Key_Left:
                        applications.moveCurrentIndexLeft();
                        break;
                    case Qt.Key_Right:
                        applications.moveCurrentIndexRight();
                        break;
                    case Qt.Key_Return:
                    case Qt.Key_Enter:
                        Applications.execute(applications.currentItem.ident);
                        break;
                    default:
                        accept = false;
                }
                event.accepted = accept;
            }

            Pandora.onPressed: {
                var accept = true;
                switch(event.key) {
                    case Pandora.DPadUp:
                        applications.moveCurrentIndexUp();
                        break;
                    case Pandora.DPadDown:
                        applications.moveCurrentIndexDown();
                        break;
                    case Pandora.DPadLeft:
                        applications.moveCurrentIndexLeft();
                        break;
                    case Pandora.DPadRight:
                        applications.moveCurrentIndexRight();
                        break;
                    case Pandora.ButtonB:
                        Applications.execute(applications.currentItem.ident);
                        break;
                    default:
                        accept = false;
                }
                event.accepted = accept;
            }

            delegate: Item {
                property string ident: identifier
                width: applications.itemSize - applications.itemSpacing/2
                height: applications.itemSize - applications.itemSpacing/2

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        applications.currentIndex = index;
                    }
                    onDoubleClicked: {
                        Applications.execute(applications.currentItem.ident);
                    }
                }
                Image {
                    id: iconField
                    source: icon ? icon : "images/application-x-executable.png"
                    smooth: false
                    anchors.fill: parent
                    anchors.margins: 4                
                }
                Text {
                    text: name

                    font.pixelSize: parent.height / 8
                    style: Text.Outline; styleColor: "#ddd"
                    color: "#222"
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 2
                    wrapMode: Text.WordWrap
                }
            }
        }
    }
}
