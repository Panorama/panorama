import Qt 4.7
import "qml" as Extensions
import Qt.labs.particles 1.0
import Panorama.Settings 1.0
import Panorama.UI 1.0
import Panorama.SystemInformation 1.0
import Panorama.Applications 1.0

PanoramaUI {
    id: ui
    name: "Magma"
    description: "An UI that will burn your fingers"
    author: "dflemstr"
    anchors.fill: parent

    property int level: 0
    property string topSection: ""

    Setting {
        id: favorites
        section: "system"
        key: "favorites"
    }

    Setting {
        id: magmaStream
        section: "magma"
        key: "magmaStream"
        defaultValue: "false"
    }

    Setting {
        id: volcano
        section: "magma"
        key: "volcano"
        defaultValue: "true"
    }

    Rectangle {
        z: -2
        anchors.fill: parent
        color: "#000022"
    }

    Item {
        id: background
        z: -1
        width: parent.width
        height: parent.height * 2
        Timer {
            interval: 200
            running: level == 0 && volcano.value == "true"
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
        Rectangle {
            x: 0
            y: ui.height
            width: ui.width
            height: ui.height
            z: -1
            color: "black"
            clip: true
        }
        Item {
            x: ui.width / 2
            y: ui.height
            width: 132
            height: ui.height
            clip: true
            opacity: magmaStream.value == "true" ? 1 : 0

            Image {
                id: stream
                NumberAnimation on y {
                    running: level == 1 && magmaStream.value == "true"
                    loops: Animation.Infinite
                    from: 0
                    to: -413
                    duration: 5000
                }
                height: ui.height + 413
                fillMode: Image.TileVertically
                source: "images/stream.png"
            }
            Image {
                z: 1
                height: ui.height
                fillMode: Image.Stretch
                source: "overlays/fragments.png"
            }
        }
    }

    FocusScope {
        id: level0
        focus: level == 0
        anchors.top: background.top
        width: parent.width
        height: parent.height
        clip: true
        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: time.hour + ":" + time.minute
            Timer {
                id: time
                property string hour: "00"
                property string minute: "00"
                interval: 1000
                running: true
                repeat: true
                triggeredOnStart: true
                onTriggered: {
                    var date = new Date;
                    var h = date.getHours().toString();
                    if(h.length == 1)
                        h = "0" + h;
                    hour = h;
                    var m = date.getMinutes().toString();
                    if(m.length == 1)
                        m = "0" + m;
                    minute = m;
                }
            }
            color: "#000044"
            font.pixelSize: ui.height / 6
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
                title: "System info"
                section: "sys"
            }
            ListElement {
                title: "Settings"
                section: "setts"
            }
        }
        ListView {
            function setSection(section) {
                topSection = section;
                level = 1;
            }

            id: topMenu
            focus: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: ui.height / 32
            anchors.horizontalCenter: parent.horizontalCenter
            height: ui.height / 16
            width: parent.width - 20
            orientation: ListView.Horizontal
            model: menu
            //overShoot: false
            spacing: 6
            Keys.onEnterPressed: {
                setSection(topMenu.currentItem.sect);
            }
            Keys.onReturnPressed: {
                setSection(topMenu.currentItem.sect);
            }
            delegate: Text {
                property string sect: section
                text: title + " "
                font.pixelSize: ui.height / 16
                color: "#222222"
                Rectangle {
                    z: -1
                    anchors.fill: parent
                    anchors.topMargin: -2
                    anchors.bottomMargin: -2
                    anchors.leftMargin: -2
                    anchors.rightMargin: -2
                    radius: 2
                    color: ListView.isCurrentItem ? "#111111" : "black"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        topMenu.currentIndex = index;
                        ui.topSection = section;
                        ui.level = 1;
                    }
                }
            }
        }
    }
    Item {
        id: level1
        anchors.top: level0.bottom
        width: parent.width
        height: parent.height
        clip: true
        Keys.onDigit2Pressed: {
            level = 0;
        }
        Keys.onEscapePressed: {
            level = 0;
        }

        Item {
            anchors.fill: parent
            anchors.topMargin: 32
            anchors.bottomMargin: 16
            anchors.leftMargin: 16
            anchors.rightMargin: 16

            Text {
                z: 6
                anchors.top: parent.top
                anchors.topMargin: -32
                anchors.left: parent.left
                anchors.leftMargin: 8
                font.pixelSize: Math.max(1, parent.height / 30)
                font.bold: true
                color: "white"
                text: "Back"
                MouseArea {
                    anchors.fill: parent
                    onClicked: level = 0;
                }
                Rectangle {
                    z: -1
                    anchors.fill: parent
                    anchors.topMargin: -2
                    anchors.bottomMargin: -2
                    anchors.leftMargin: -2
                    anchors.rightMargin: -2
                    color: "#900000"
                    radius: 2
                }
            }

            //Applications:
            FocusScope {
                id: apps
                anchors.fill: parent
                focus: level == 1 && topSection == "apps"
                opacity: topSection == "apps" ? 1 : 0

                Extensions.ApplicationViewer {
                    function toggleFavorite(idf) {
                        if(favorites.value.indexOf(idf) == -1) {
                            //Add favorite
                            if(favorites.value.length > 0)
                                favorites.value += "|";
                            favorites.value += idf;
                        }
                        else //Remove favorite if it already exists
                        {
                            var nf = favorites.value.replace(idf, "");
                            nf = nf.replace("||", "|");
                            favorites.value = nf.replace(/\|$|^\|/, "");
                        }
                    }

                    id: appsViewer
                    anchors.fill: parent
                    model: Applications.list.matching("name", nameFilter).sortedBy("name", true)
                    onSelected: Applications.execute(id);
                    onFavStarClicked: toggleFavorite(id);
                    onPressed2: level = 0;
                    onPressed3: toggleFavorite(appsViewer.currentItem.ident);
                }
            }

            //Favorites:
            FocusScope {
                id: favs
                anchors.fill: parent
                focus: level == 1 && topSection == "favs"
                opacity: topSection == "favs" ? 1 : 0

                Extensions.ApplicationViewer {
                    function removeFavorite(idf) {
                        var nf = favorites.value.replace(idf, "");
                        nf = nf.replace("||", "|");
                        favorites.value = nf.replace(/\|$|^\|/, "");
                        if(favorites.value.length == 0)
                            level = 0;
                    }

                    id: favsViewer
                    anchors.fill: parent
                    model: Applications.list.matching("name", nameFilter).matching("identifier", "^" + favorites.value + "$").sortedBy("name", true)

                    onSelected: Applications.execute(id);
                    onFavStarClicked: removeFavorite(id);
                    focus: true
                    onPressed2: level = 0;
                    onPressed3: removeFavorite(favsViewer.currentItem.ident);
                }
                Text {
                    anchors.centerIn: parent
                    z: 5
                    text: "Use the bottom action button (or the 3 key) to add an application to your favorites"
                    color: "gray"
                    font.pointSize: 12
                    opacity: favorites.value.length == 0 ? 1 : 0
                }
            }

            //System information:
            FocusScope {
                anchors.fill: parent
                focus: level == 1 && topSection == "sys"
                opacity: topSection == "sys" ? 1 : 0
                Column {
                    anchors.fill: parent
                    Text {
                        text: "CPU:"
                        height: ui.height / 30
                        width: parent.width - 10
                        color: "#f7c767"
                        font.bold: true
                        font.pixelSize: height * 0.8
                        verticalAlignment: Text.AlignBottom
                    }
                    Extensions.ProgressBar {
                        width: parent.width - 10
                        maximum: SystemInformation.cpu
                        value: SystemInformation.usedCpu
                        unit: "%"
                        color: "#f7c767"
                        secondColor: "#ed8d06"
                        textColor: "#f7c767"
                        style: Text.Outline
                        styleColor: "#300000"
                        displayInPercent: true
                    }
                    Text {
                        text: "RAM:"
                        height: ui.height / 30
                        width: parent.width - 10
                        color: "#f7c767"
                        font.bold: true
                        font.pixelSize: height * 0.8
                        verticalAlignment: Text.AlignBottom
                    }
                    Extensions.ProgressBar {
                        width: parent.width - 10
                        maximum: SystemInformation.ram
                        value: SystemInformation.usedRam
                        unit: "MiB"
                        color: "#ed8d06"
                        secondColor: "#d84800"
                        textColor: "#f7c767"
                        style: Text.Outline
                        styleColor: "#300000"
                    }
                    Text {
                        text: "Swap:"
                        height: ui.height / 30
                        width: parent.width - 10
                        color: "#f7c767"
                        font.bold: true
                        font.pixelSize: height * 0.8
                        verticalAlignment: Text.AlignBottom
                    }
                    Extensions.ProgressBar {
                        width: parent.width - 10
                        maximum: SystemInformation.swap
                        value: SystemInformation.usedSwap
                        unit: "MiB"
                        color: "#d84800"
                        secondColor: "#900000"
                        textColor: "#f7c767"
                        style: Text.Outline
                        styleColor: "#300000"
                    }
                    Text {
                        text: "Disk usage - SD1:"
                        height: ui.height / 30
                        width: parent.width - 10
                        color: "#f7c767"
                        font.bold: true
                        font.pixelSize: height * 0.8
                        verticalAlignment: Text.AlignBottom
                    }
                    Extensions.ProgressBar {
                        width: parent.width - 10
                        maximum: SystemInformation.sd1
                        value: SystemInformation.usedSd1
                        unit: "MiB"
                        color: "#900000"
                        secondColor: "#300000"
                        textColor: "#f7c767"
                        style: Text.Outline
                        styleColor: "#300000"
                    }
                    Text {
                        text: "Disk usage - SD2:"
                        height: ui.height / 30
                        width: parent.width - 10
                        color: "#f7c767"
                        font.bold: true
                        font.pixelSize: height * 0.8
                        verticalAlignment: Text.AlignBottom
                    }
                    Extensions.ProgressBar {
                        width: parent.width - 10
                        maximum: SystemInformation.sd2
                        value: SystemInformation.usedSd2
                        unit: "MiB"
                        color: "#6F0B00"
                        secondColor: "#370400"
                        textColor: "#f7c767"
                        style: Text.Outline
                        styleColor: "#300000"
                    }
                }
            }

            //Settings:
            FocusScope {
                id: setts
                anchors.fill: parent
                focus: level == 1 && topSection == "setts"
                opacity: topSection == "setts" ? 1 : 0
                Text {
                    anchors.centerIn: parent
                    z: 5
                    text: "Nothing to see here, move along :-)"
                    color: "gray"
                    font.pointSize: 12
                }
            }
        }
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
        }
    ]
    transitions: [
        Transition {
            NumberAnimation {
                properties: "y"
                duration: 500
                easing.type: Easing.InOutQuart
            }
        }
    ]
}
