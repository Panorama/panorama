import Qt 4.7                   //Import Qt
import Panorama 1.0             //Import Panorama extensions

PanoramaUI {
    id: ui
    name: "Tabbed"
    description: "A tab based UI"
    author: "B-ZaR"

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
        id: tabContainer
        color: "#222"
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 170

        Column {
            id: tabs
            property int selected: 0
            property string selectedName: tabs.children[selected].fullName
            property string selectedRawName: tabs.children[selected].rawName
            anchors.fill: parent
            anchors.topMargin: (parent.height % 10) / 2
            anchors.bottomMargin: (parent.height % 10) / 2

            function nextTab() {
                selected = (selected + 1) % 10;
                applications.currentIndex = 0;
            }

            function prevTab() {
                selected = (selected > 0) ? (selected - 1) : 9;
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
                if(event.key == Pandora.TriggerR) {
                    prevTab();
                    event.accepted = true;
                } else if(event.key == Pandora.TriggerL) {
                    nextTab();
                    event.accepted = true;
                }
            }

            Repeater {
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
                        name: "Other"
                        raw: "NoCategory"
                    }
                }
                delegate: Rectangle {
                    property string rawName: raw
                    property string fullName: name
                    property string tabIndex: index
                    property bool selected

                    border {
                        color: "#333"
                        width: 1
                    }
                    height: tabs.height/10
                    width: tabs.width
                    color: "#444"

                    selected: tabs.selected == tabIndex
                    Rectangle {
                        x: 63
                        y: -63
                        width:parent.height
                        height:parent.width
                        rotation: 90
                        opacity: parent.selected ? 1.0 : 0.0
                        gradient: Gradient { GradientStop { position: 0.0; color: "#eee" } GradientStop { position: 1.0; color: "#ccc" } }
                    }
                    MouseArea {
                        anchors.fill: parent

                        onClicked: {
                            tabs.selected = parent.tabIndex;
                            applications.currentIndex = 0;
                        }
                    }
                    Text {
                        text: fullName
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                        anchors.margins: 2
                        font.pixelSize: parent.height/2
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
        anchors.left: tabContainer.right
        anchors.right: parent.right
        radius: (tabContainer.height % 10) / 2
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
            highlight: Rectangle { color: "#555"; opacity: 0.5; radius: 8; width: 64; height: 64 }
            anchors.fill: parent
            anchors.margins: 10

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
                width: parent.width/8
                height: parent.width/8

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
                    smooth: true
                    anchors.fill: parent
                    anchors.margins: 4

                }
                Text {
                    text: name

                    font.pixelSize: 10
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
