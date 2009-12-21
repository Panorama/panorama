import Qt 4.6
import Panorama 1.0
import "qml" as Helpers

PanoramaUI {
    id: ui
    name: "PMenu compatibility user interface"
    description: "Put this file inside of a PMenu theme to make a Panorama UI out of it!"
    author: "dflemstr"
    settingsKey: "pmenu-colors"

    TextFile { id: skinCfg; source: "skin.cfg" } //TextFile isn't standard QML, but part of Panorama 1.0

    Script {
        //For readField()
        source: "qml/text.js"
    }

    //Specifies the opacity for each page
    property real emulatorsOpacity: 0
    property real gamesOpacity: 0
    property real miscOpacity: 0
    property real mediaOpacity: 0
    property real favoritesOpacity: 0
    property real settingsOpacity: 0

    //Specifies which page is visible
    property int selectedIndex: 0

    //Show the "Add/remove XYZ from favorites?" dialog?
    property bool showFavDialog: false

    //A collection of application IDs representing our favorites
    //Stored as "id1|id2|id3" so that we can use it as a regex as well as a list
    property string favorites: sharedSetting("system", "favorites")

    property int clockspeed: parseInt(sharedSetting("system", "clockspeed"))

    //------------------------------PMenu properties------------------------------
    property string backgroundApplications: readField(skinCfg.data, "background_applications")
    property string backgroundMedia: readField(skinCfg.data, "background_media")
    property string backgroundSettings: readField(skinCfg.data, "background_settings")

    property int applicationsBoxX: readField(skinCfg.data, "applications_box_x")
    property int applicationsBoxY: readField(skinCfg.data, "applications_box_y")
    property int applicationsBoxWidth: readField(skinCfg.data, "applications_box_w")
    property string applicationHighlight: readField(skinCfg.data, "application_highlight")

    property int iconScaleMax: readField(skinCfg.data, "icon_scale_max")
    property int iconScaleMin: readField(skinCfg.data, "icon_scale_min")
    property int applicationsSpacing: readField(skinCfg.data, "applications_spacing")
    property int applicationsTitleDescriptionY: readField(skinCfg.data, "applications_title_description_y")
    property int maxAppsPerPage: readField(skinCfg.data, "max_app_per_page")

    property string confirmBox: readField(skinCfg.data, "confirm_box")
    property int confirmBoxX: readField(skinCfg.data, "confirm_box_x")
    property int confirmBoxY: readField(skinCfg.data, "confirm_box_y")

    property int previewPicX: readField(skinCfg.data, "preview_pic_x")
    property int previewPicY: readField(skinCfg.data, "preview_pic_y")
    property int previewPicWidth: readField(skinCfg.data, "preview_pic_w")

    property string highlight: readField(skinCfg.data, "highlight")
    property bool highlightEnabled: (readField(skinCfg.data, "highlight_enabled") != 0)

    property string mediaFileIcon: readField(skinCfg.data, "media_file_icon")
    property string mediaFolderIcon: readField(skinCfg.data, "media_folder_icon")

    property int mediaMaxFilesPerPage: readField(skinCfg.data, "media_max_files_per_page")

    property bool showCategoryTitle: (readField(skinCfg.data, "show_category_title") != 0)
    property string noIcon: readField(skinCfg.data, "no_icon")
    property string noPreview: readField(skinCfg.data, "no_preview")

    //------------------------------PMenu objects------------------------------

    Helpers.TextStyle {
        id: smallStyle
        baseName: "font_small"
        sourceData: skinCfg.data
    }

    Helpers.TextStyle {
        id: bigStyle
        baseName: "font_big"
        sourceData: skinCfg.data
    }

    Helpers.SelectionIcon {
        id: emulatorsIcon
        baseName: "emulators"
        sourceData: skinCfg.data

        bold: smallStyle.bold
        italic: smallStyle.italic
        pixelSize: smallStyle.pixelSize
        family: smallStyle.family
        color: smallStyle.color
        highlightColor: smallStyle.highlightColor

        intensity: emulatorsOpacity
    }

    Helpers.SelectionIcon {
        id: gamesIcon
        baseName: "games"
        sourceData: skinCfg.data

        bold: smallStyle.bold
        italic: smallStyle.italic
        pixelSize: smallStyle.pixelSize
        family: smallStyle.family
        color: smallStyle.color
        highlightColor: smallStyle.highlightColor

        intensity: gamesOpacity
    }

    Helpers.SelectionIcon {
        id: miscIcon
        baseName: "misc"
        sourceData: skinCfg.data

        bold: smallStyle.bold
        italic: smallStyle.italic
        pixelSize: smallStyle.pixelSize
        family: smallStyle.family
        color: smallStyle.color
        highlightColor: smallStyle.highlightColor

        intensity: miscOpacity
    }

    Helpers.SelectionIcon {
        id: mediaIcon
        baseName: "media"
        sourceData: skinCfg.data

        bold: smallStyle.bold
        italic: smallStyle.italic
        pixelSize: smallStyle.pixelSize
        family: smallStyle.family
        color: smallStyle.color
        highlightColor: smallStyle.highlightColor

        intensity: mediaOpacity
    }

    Helpers.TextStyle {
        id: mediaStyle
        baseName: "media_text"
        sourceData: skinCfg.data
    }

    Helpers.SelectionIcon {
        id: favoritesIcon
        baseName: "favorites"
        sourceData: skinCfg.data

        bold: smallStyle.bold
        italic: smallStyle.italic
        pixelSize: smallStyle.pixelSize
        family: smallStyle.family
        color: smallStyle.color
        highlightColor: smallStyle.highlightColor

        intensity: favoritesOpacity
    }

    Helpers.SelectionIcon {
        id: settingsIcon
        baseName: "settings"
        sourceData: skinCfg.data

        bold: smallStyle.bold
        italic: smallStyle.italic
        pixelSize: smallStyle.pixelSize
        family: smallStyle.family
        color: smallStyle.color
        highlightColor: smallStyle.highlightColor

        intensity: settingsOpacity
    }

    Helpers.PositionedImage {
        id: cpuIcon
        baseName: "cpu_icon"
    }
    Helpers.TextStyle {
        id: cpuStyle
        baseName: "cpu_text"
        sourceData: skinCfg.data
    }
    Helpers.PositionedText {
        id: cpuText
        baseName: "cpu_text"
        sourceData: skinCfg.data

        bold: cpuStyle.bold
        italic: cpuStyle.italic
        pixelSize: cpuStyle.pixelSize
        family: cpuStyle.family
        color: cpuStyle.color
        highlightColor: cpuStyle.highlightColor

        text: clockspeed + " MHz"
    }

    Helpers.PositionedImage {
        id: sd1Icon
        baseName: "sd1_icon"
        sourceData: skinCfg.data
    }
    Helpers.TextStyle {
        id: sd1Style
        baseName: "sd1_text"
        sourceData: skinCfg.data
    }
    Helpers.PositionedText {
        id: sd1Text
        baseName: "sd1_text"
        sourceData: skinCfg.data

        bold: sd1Style.bold
        italic: sd1Style.italic
        pixelSize: sd1Style.pixelSize
        family: sd1Style.family
        color: sd1Style.color
        highlightColor: sd1Style.highlightColor

        text: "1024 MiB"
    }

    Helpers.PositionedImage {
        id: sd2Icon
        baseName: "sd2_icon"
        sourceData: skinCfg.data
    }
    Helpers.TextStyle {
        id: sd2Style
        baseName: "sd2_text"
        sourceData: skinCfg.data
    }
    Helpers.PositionedText {
        id: sd2Text
        baseName: "sd2_text"
        sourceData: skinCfg.data

        bold: sd2Style.bold
        italic: sd2Style.italic
        pixelSize: sd2Style.pixelSize
        family: sd2Style.family
        color: sd2Style.color
        highlightColor: sd2Style.highlightColor

        text: "1024 MiB"
    }

    Helpers.PositionedImage {
        id: clockIcon
        baseName: "clock_icon"
        sourceData: skinCfg.data
    }
    Helpers.TextStyle {
        id: clockStyle
        baseName: "clock_text"
        sourceData: skinCfg.data
    }
    Helpers.PositionedText {
        id: clockText
        baseName: "clock_text"
        sourceData: skinCfg.data

        bold: clockStyle.bold
        italic: clockStyle.italic
        pixelSize: clockStyle.pixelSize
        family: clockStyle.family
        color: clockStyle.color
        highlightColor: clockStyle.highlightColor

        text: time.hour + ":" + time.minute
        Timer {
            id: time
            property string hour: "00"
            property string minute: "00"
            interval: 100
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
    }

    Keys.onLeftPressed: {
        if(selectedIndex > 0) {
            selectedIndex -= 1;
            changeState(selectedIndex);
        }
    }

    Keys.onRightPressed: {
        if(selectedIndex < 5) {
            selectedIndex += 1;
            changeState(selectedIndex);
        }
    }

    /*
    //Highlight:
    Image {
        id: highl
        opacity: SequentialAnimation {
            running: true
            repeat: true

            NumberAnimation {
                from: 0
                to: highlightEnabled ? 1 : 0
                easing: "easeOutCubic"
                duration: 1000
            }
            NumberAnimation {
                from: highlightEnabled ? 1 : 0
                to: 0
                easing: "easeInCubic"
                duration: 1000
            }
        }
        source: highlight
    }

    //Dialog:
    Image {
        id: favoriteDialog
        opacity: showFavDialog ? 1 : 0
        source: confirmBox
        z: 5
        x: confirmBoxX - width / 2
        y: confirmBoxY - height / 2
        focus: showFavDialog
        Keys.onDigit1Pressed: {
            var idf = appBrowser.currentItem.ident;
            if(ui.selectedIndex == 4) {
                favorites = favorites.replace(idf, "");
                favorites = favorites.replace("||", "");
                favorites = favorites.replace(/\|$|^\|/, "");
            }
            else if(favorites.indexOf(idf) == -1) {
                if(favorites.length > 0)
                    favorites += "|";
                favorites += idf;
                setSharedSetting("system", "favorites", favorites);
            }
            showFavDialog = false;
        }
        Keys.onDigit2Pressed: {
            showFavDialog = false;
        }
        Text {
            anchors.centerIn: parent
            width: parent.width
            text: (ui.selectedIndex != 4) ? ("Do you want to add \"" +
                        appBrowser.currentItem.friendlyName + "\" to your favorites?")
                  : ("Do you want to remove \"" + appBrowser.currentItem.friendlyName +
                        "\" from your favorites?")
            wrap: true

            color: smallFontColor
            font.bold: smallFont.bold
            font.italic: smallFont.italic
            font.pixelSize: smallFont.pixelSize
            font.family: smallFont.family
        }
    }

    //The settings page:
    Item {
        id: settingsPage
        x: applicationsBoxX
        y: applicationsBoxY
        width: applicationsBoxWidth
        height: (iconScaleMin + applicationsSpacing * 0.5) * maxAppsPerPage
        opacity: settingsOpacity
        focus: ui.selectedIndex == 5

        property int clockspeed: ui.sharedSetting("system", "clockspeed")

        Keys.onUpPressed: {
            if(settingsPage.clockspeed < 800) {
                settingsPage.clockspeed += 10;
                ui.setSharedSetting("system", "clockspeed", settingsPage.clockspeed);
            }
        }
        Keys.onDownPressed: {
            if(settingsPage.clockspeed > 300) {
                settingsPage.clockspeed -= 10;
                ui.setSharedSetting("system", "clockspeed", settingsPage.clockspeed);
            }
        }
        Column {
            anchors.fill: parent
            Row {
                Text {
                    text: "Clockspeed: "
                    color: smallFontHighlightColor
                    font.bold: smallFont.bold
                    font.italic: smallFont.italic
                    font.pixelSize: smallFont.pixelSize
                    font.family: smallFont.family
                }
                Text {
                    text: settingsPage.clockspeed
                    color: smallFontColor
                    font.bold: smallFont.bold
                    font.italic: smallFont.italic
                    font.pixelSize: smallFont.pixelSize
                    font.family: smallFont.family
                }
            }
        }
    }

    Item {
        id: mediaBrowser
        focus: !showFavDialog && (ui.selectedIndex == 3)
    }

    //The applications browser:
    Item {
        x: applicationsBoxX -5
        y: applicationsBoxY - 20
        width: applicationsBoxWidth + 10
        height: (iconScaleMin + applicationsSpacing * 0.5) * maxAppsPerPage + 40
        clip: true
        Keys.onDigit2Pressed: { //The rightmost Pandora button
            ui.showFavDialog = true;
        }
        Keys.onDigit1Pressed: {
            execute(appBrowser.currentItem.ident);
        }
        ListView {
            id: appBrowser
            anchors.fill: parent
            anchors.topMargin: 20
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.bottomMargin: 20
            focus: !showFavDialog && (ui.selectedIndex == 0 || ui.selectedIndex == 1 || ui.selectedIndex == 2 || ui.selectedIndex == 4)
            model: (ui.selectedIndex == 0) ? ui.applications.inCategory("Emulator").sortedBy("name", true)
                 : (ui.selectedIndex == 1) ? ui.applications.inCategory("Game").sortedBy("name", true)
                 : (ui.selectedIndex == 2) ? ui.applications.inCategory("^(?!Game|Emulator)$").sortedBy("name", true)
                 : (ui.selectedIndex == 4 && favorites.length > 0) ?
                    ui.applications.matching("identifier", favorites).sortedBy("name", true)
                 : ui.applications.matching("identifier", "^$") //Lists nothing

            opacity: Math.max(emusOpacity, Math.max(gamesOpacity, Math.max(miscOpacity, favoritesOpacity)))
            spacing: applicationsSpacing * 0.5
            clip: true
            Component {
                id: appHighlight
                Item {
                    y: SpringFollow {
                        source: appBrowser.currentItem.y
                        spring: 3
                        damping: 0.2
                    }
                    clip: false
                    Image {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        source: applicationHighlight
                        fillMode: Image.PreserveAspectCrop
                    }
                }
            }
            highlight: appHighlight
            highlightFollowsCurrentItem: false
            delegate: Item {
                id: deleg
                width: applicationsBoxWidth
                height: iconScaleMin
                property string ident: identifier
                property string friendlyName: name
                MouseRegion {
                    anchors.fill: parent
                    onClicked: appBrowser.currentIndex = index
                }
                Row {
                    anchors.fill: parent
                    Image {
                        source: icon
                        width: iconScaleMin
                        height: iconScaleMin
                        smooth: true
                    }
                    Item {
                        width: 5
                        height: iconScaleMin
                    }
                    Column {
                        width: parent.width - iconScaleMin
                        anchors.verticalCenter: parent.verticalCenter
                        Text {
                            color: deleg.isCurrentItem ?
                                ui.bigFontColorHighlight : ui.bigFontColor
                            font.bold: bigFont.bold
                            font.italic: bigFont.italic
                            font.pixelSize: bigFont.pixelSize
                            font.family: bigFont.family
                            elide: Text.ElideRight
                            text: name
                        }
                        Text {
                            color: deleg.isCurrentItem ?
                                ui.smallFontColorHighlight : ui.smallFontColor
                            font.bold: smallFont.bold
                            font.italic: smallFont.italic
                            font.pixelSize: smallFont.pixelSize
                            font.family: smallFont.family
                            elide: Text.ElideRight
                            text: comment
                        }
                    }
                }
            }
        }
    }*/

    state: selectedIndex == 0 ? "emulators"
         : selectedIndex == 1 ? "games"
         : selectedIndex == 2 ? "misc"
         : selectedIndex == 3 ? "media"
         : selectedIndex == 4 ? "favorites"
         : selectedIndex == 5 ? "settings"
         : ""

    states: [
        State {
            name: "emulators"
            PropertyChanges {
                target: ui
                selectedIndex: 0
                emulatorsOpacity: 1
            }
            /*PropertyChanges {
                target: highl
                x: emulatorsIconX - width / 2
                y: emulatorsIconY - height / 2
            }*/
        },
        State {
            name: "games"
            PropertyChanges {
                target: ui
                selectedIndex: 1
                gamesOpacity: 1
            }
            PropertyChanges {
                target: highl
                x: gamesIconX - width / 2
                y: gamesIconY - height / 2
            }
        },
        State {
            name: "misc"
            PropertyChanges {
                target: ui
                selectedIndex: 2
                miscOpacity: 1
            }
            PropertyChanges {
                target: highl
                x: miscIconX - width / 2
                y: miscIconY - height / 2
            }
        },
        State {
            name: "media"
            PropertyChanges {
                target: ui
                selectedIndex: 3
                mediaOpacity: 1
            }
            PropertyChanges {
                target: highl
                x: mediaIconX - width / 2
                y: mediaIconY - height / 2
            }
        },
        State {
            name: "favorites"
            PropertyChanges {
                target: ui
                selectedIndex: 4
                favoritesOpacity: 1
            }
            PropertyChanges {
                target: highl
                x: favoritesIconX - width / 2
                y: favoritesIconY - height / 2
            }
        },
        State {
            name: "settings"
            PropertyChanges {
                target: ui
                selectedIndex: 5
                settingsOpacity: 1
            }
            PropertyChanges {
                target: highl
                x: settingsIconX - width / 2
                y: settingsIconY - height / 2
            }
        }
    ]

    transitions: [
        Transition {
            to: "settings"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    matchProperties: "x,y"
                    easing: "easeOutQuad"
                }
                NumberAnimation {
                    duration: 200
                    matchProperties: "settingsOpacity"
                    easing: "easeLinear"
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        matchProperties: "emusOpacity,gamesOpacity,miscOpacity,mediaOpacity,favoritesOpacity"
                        easing: "easeOutQuad"
                    }
                }
            }
        },
        Transition {
            to: "emulators"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    matchProperties: "x,y"
                    easing: "easeOutQuad"
                }
                NumberAnimation {
                    duration: 200
                    matchProperties: "emusOpacity"
                    easing: "easeLinear"
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        matchProperties: "settingsOpacity,gamesOpacity,miscOpacity,mediaOpacity,favoritesOpacity"
                        easing: "easeOutQuad"
                    }
                }
            }
        },
        Transition {
            to: "games"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    matchProperties: "x,y"
                    easing: "easeOutQuad"
                }
                NumberAnimation {
                    duration: 200
                    matchProperties: "gamesOpacity"
                    easing: "easeLinear"
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        matchProperties: "settingsOpacity,emusOpacity,miscOpacity,mediaOpacity,favoritesOpacity"
                        easing: "easeOutQuad"
                    }
                }
            }
        },
        Transition {
            to: "misc"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    matchProperties: "x,y"
                    easing: "easeOutQuad"
                }
                NumberAnimation {
                    duration: 200
                    matchProperties: "miscOpacity"
                    easing: "easeLinear"
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        matchProperties: "settingsOpacity,gamesOpacity,emusOpacity,mediaOpacity,favoritesOpacity"
                        easing: "easeOutQuad"
                    }
                }
            }
        },
        Transition {
            to: "media"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    matchProperties: "x,y"
                    easing: "easeOutQuad"
                }
                NumberAnimation {
                    duration: 200
                    matchProperties: "mediaOpacity"
                    easing: "easeLinear"
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        matchProperties: "settingsOpacity,gamesOpacity,miscOpacity,emusOpacity,favoritesOpacity"
                        easing: "easeOutQuad"
                    }
                }
            }
        },
        Transition {
            to: "favorites"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    matchProperties: "x,y"
                    easing: "easeOutQuad"
                }
                NumberAnimation {
                    duration: 200
                    matchProperties: "favoritesOpacity"
                    easing: "easeLinear"
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        matchProperties: "settingsOpacity,gamesOpacity,miscOpacity,mediaOpacity,emusOpacity"
                        easing: "easeOutQuad"
                    }
                }
            }
        }
    ]
}
