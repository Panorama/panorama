import Qt 4.6
import Panorama 1.0
import "qml" as Extensions

PanoramaUI {
    id: ui
    name: "Magma"
    description: "An UI that will burn your fingers"
    author: "dflemstr"
    settingsSection: "magma"

    property int level: 0
    property string topSection: ""
    
    Setting {
        id: favorites
        section: "system"
        key: "favorites"
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
            running: level == 0
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
            anchors.horizontalCenter: flow.horizontalCenter
            y: ui.height
            width: 132
            height: ui.height
            clip: true
            /* Not yet implemented in QML
            effect: Bloom {
                blurHint: Qt.PerformanceHint
                blurRadius: 8
            }*/
            Image {
                id: stream
                y: SequentialAnimation {
                    id: seq
                    running: level == 1
                    repeat: true
                    NumberAnimation {
                        from: 0
                        to: -413
                        duration: 5000
                    }
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
            text: "My Pandora"
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
        Script {
            function setSection(section) {
                topSection = section;
                level = 1;
            }
        }
        ListView {
            id: topMenu
            focus: true
            anchors.bottom: parent.bottom
            anchors.bottomMargin: ui.height / 32
            anchors.horizontalCenter: parent.horizontalCenter
            height: ui.height / 16
            width: parent.width - 20
            orientation: ListView.Horizontal
            model: menu
            overShoot: false
            spacing: 6
            Keys.onDigit1Pressed: {
                setSection(topMenu.currentItem.sect);
            }
            Keys.onSpacePressed: {
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
                MouseRegion {
                    anchors.fill: parent
                    onClicked: {
                        topMenu.currentIndex = index;
                        setSection(section);
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
        
        Text {
            z: 6
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.leftMargin: 8
            font.pixelSize: ui.height / 30
            font.bold: true
            color: "white"
            text: "Back"
            MouseRegion {
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
                color: "gray"
                radius: 2
            }
        }
        
        Item {
            anchors.fill: parent
            anchors.topMargin: 16
            anchors.bottomMargin: 16
            anchors.leftMargin: 16
            anchors.rightMargin: 16
            
            //Applications:
            FocusScope {
                id: apps
                anchors.fill: parent
                focus: level == 1 && topSection == "apps"
                opacity: topSection == "apps" ? 1 : 0
                
                Script {
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
                }
                
                Keys.onDigit3Pressed: toggleFavorite(appsViewer.currentItem.ident);
                
                Extensions.ApplicationViewer {
                    id: appsViewer
                    anchors.fill: parent
                    model: ui.applications.sortedBy("name", true)
                    onSelected: ui.execute(id);
                    onFavStarClicked: toggleFavorite(id);
                }
            }
            
            //Favorites:
            FocusScope {
                id: favs
                anchors.fill: parent
                focus: level == 1 && topSection == "favs"
                opacity: topSection == "favs" ? 1 : 0
                
                Script {
                    function removeFavorite(idf) {
                        var nf = favorites.value.replace(idf, "");
                        nf = nf.replace("||", "|");
                        favorites.value = nf.replace(/\|$|^\|/, "");
                        if(favorites.value.length == 0)
                            level = 0;
                    }
                }
                
                Keys.onDigit3Pressed: removeFavorite(favsViewer.currentItem.ident);
                
                Extensions.ApplicationViewer {
                    id: favsViewer
                    anchors.fill: parent
                    model: ui.applications.matching("identifier", "^" + favorites.value + "$").sortedBy("name", true)
                    onSelected: ui.execute(id);
                    onFavStarClicked: removeFavorite(id);
                    focus: true
                }
                Text {
                    anchors.centerIn: parent
                    z: 5
                    text: "Use the bottom action button (or the 3 key) to add an application to your favorites"
                    color: "white"
                    font.pointSize: 12
                    opacity: favorites.value.length == 0 ? 1 : 0
                }
            }
            
            //System information:
            FocusScope {
                anchors.fill: parent
                focus: level == 1 && topSection == "sys"
                opacity: topSection == "sys" ? 1 : 0
                SystemInformation {
                    id: sysinfo
                }
                Text {
                    id: ramText
                    text: "RAM:"
                    height: ui.height / 16
                    width: parent.width
                    color: "white"
                    font.bold: true
                    font.pixelSize: height * 0.8
                }
                Extensions.ProgressBar {
                    id: ramBar
                    anchors.top: ramText.bottom
                    width: parent.width
                    maximum: sysinfo.ram
                    value: sysinfo.usedRam
                    unit: "MiB"
                    color: "steelblue"
                    secondColor: "blue"
                }
                Text {
                    id: swapText
                    anchors.top: ramBar.bottom
                    text: "Swap:"
                    height: ui.height / 16
                    width: parent.width
                    color: "white"
                    font.bold: true
                    font.pixelSize: height * 0.8
                }
                Extensions.ProgressBar {
                    id: swapBar
                    anchors.top: swapText.bottom
                    width: parent.width
                    maximum: sysinfo.swap
                    value: sysinfo.usedSwap
                    unit: "MiB"
                    color: "red"
                    secondColor: "darkred"
                }
                /*Text {
                    color: "white"
                    font.pixelSize: ui.height / 30
                    text: "<table><tr><th>Resource</th><th>Used</th>" + 
                        "<th></th><th>Total</th><th></th></tr>" +
                        "<tr><td>RAM</td><td>" + sysinfo.usedRam + "</td>" +
                        "<td>/</td><td>" + sysinfo.ram + "</td><td>MiB</td></tr>" +
                        "<tr><td>Swap</td><td>" + sysinfo.usedSwap + "</td>" +
                        "<td>/</td><td>" + sysinfo.swap + "</td><td>MiB</td></tr>" +
                        "<tr><td>SD 1</td><td>" + sysinfo.usedSd1 + "</td>" +
                        "<td>/</td><td>" + sysinfo.sd1 + "</td><td>MiB</td></tr>" +
                        "<tr><td>SD 2</td><td>" + sysinfo.usedSd2 + "</td>" +
                        "<td>/</td><td>" + sysinfo.sd2 + "</td><td>MiB</td></tr>" + 
                        "</table>"
                }*/
            }
            
            //Settings:
            FocusScope {
                id: setts
                anchors.fill: parent
                focus: level == 1 && topSection == "setts"
                opacity: topSection == "setts" ? 1 : 0
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
                matchProperties: "y"
                duration: 500
                easing: "easeInOutQuart"
            }
        }
    ]
}
