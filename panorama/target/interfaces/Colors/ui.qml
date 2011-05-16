import Qt 4.7
import Panorama 1.0
import Panorama.TextFile 1.0
import Panorama.SystemInformation 1.0
import Panorama.Pandora 1.0
import Panorama.Applications 1.0
import "qml" as Helpers
import "qml/parser.js" as Parser
PanoramaUI {
    id: ui
    name: "Colors (from PMenu)"
    description: "Put this file inside of a PMenu theme to make a Panorama UI out of it!"
    author: "dflemstr"

    TextFile { //TextFile isn't standard QML, but part of Panorama 1.0
        id: skinCfg
        source: "skin.cfg"
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

    focus: !appBrowser.focus && !mediaBrowser.focus && !showFavDialog

    //Switch active page using arrow keys
    Keys.onLeftPressed: {
        if(selectedIndex > 0 && !showFavDialog)
            selectedIndex -= 1;
    }

    Keys.onRightPressed: {
        if(selectedIndex < 5 && !showFavDialog)
            selectedIndex += 1;
    }

    //Show the "Add/remove XYZ from favorites?" dialog?
    property bool showFavDialog: false

    //A collection of application IDs representing our favorites
    //Stored as "id1|id2|id3" so that we can use it as a regex as well as a list
    Setting { id: favorites; section: "system"; key: "favorites" }

    //The clockspeed setting, stored as an integer in MHz
    Setting { id: clockspeed; section: "system"; key: "clockspeed"; defaultValue: 0 }

    //------------------------------PMenu properties----------------------------

    //Generic properties that cannot be modelled using object-oriented models

    property int applicationsBoxX: Parser.readField(skinCfg.data, "applications_box_x")
    property int applicationsBoxY: Parser.readField(skinCfg.data, "applications_box_y")
    property int applicationsBoxWidth: Parser.readField(skinCfg.data, "applications_box_w")
    property string applicationHighlight: Parser.readField(skinCfg.data, "application_highlight")

    property int iconScaleMax: Parser.readField(skinCfg.data, "icon_scale_max")
    property int iconScaleMin: Parser.readField(skinCfg.data, "icon_scale_min")
    property int applicationsSpacing: Parser.readField(skinCfg.data, "applications_spacing")
    property int applicationsTitleDescriptionY: Parser.readField(skinCfg.data, "applications_title_description_y")
    property int maxAppsPerPage: Parser.readField(skinCfg.data, "max_app_per_page")

    /* TODO: implement... but normal launchers don't really have previews??
    property int previewPicX: readField(skinCfg.data, "preview_pic_x")
    property int previewPicY: readField(skinCfg.data, "preview_pic_y")
    property int previewPicWidth: readField(skinCfg.data, "preview_pic_w")
    */

    property string highlight: Parser.readField(skinCfg.data, "highlight")
    property bool highlightEnabled: (Parser.readField(skinCfg.data, "highlight_enabled") != 0)

    /* TODO: implement
    property string mediaFileIcon: readField(skinCfg.data, "media_file_icon")
    property string mediaFolderIcon: readField(skinCfg.data, "media_folder_icon")

    property int mediaMaxFilesPerPage: readField(skinCfg.data, "media_max_files_per_page")
    */

    /* TODO: implement
    property bool showCategoryTitle: (readField(skinCfg.data, "show_category_title") != 0) */
    property string noIcon: Parser.readField(skinCfg.data, "no_icon")
    /* TODO: see above
    property string noPreview: readField(skinCfg.data, "no_preview")*/

    //------------------------------Backgrounds---------------------------------

    //Self-explanatory. Each background has z-index -1 because it has to stay
    //behind other objects...

    Image {
        source: Parser.readField(skinCfg.data, "background_applications")
        x: 0
        y: 0
        z: -1
        opacity: Math.max(Math.max(miscOpacity, favoritesOpacity), Math.max(gamesOpacity, emulatorsOpacity))
    }

    Image {
        source: Parser.readField(skinCfg.data, "background_media")
        x: 0
        y: 0
        z: -1
        opacity: mediaOpacity
    }

    Image {
        source: Parser.readField(skinCfg.data, "background_settings")
        x: 0
        y: 0
        z: -1
        opacity: settingsOpacity
    }

    //------------------------------PMenu objects-------------------------------

    //Each helper object below has a function called "accessor". It uses that
    //function internally to load resources by calling e.g. "accessor('_icon_x')"
    //We need to override that function to point it to the right resource.

    /*
     * TextStyles:
     *
     * - Each text style has a "getField()" method that can be used to get a
     *   certain style property. Normal properties cannot be used because of the
     *   inverse initialization order of the TextFile object above
     *
     * - "fontify" indicates that "_font" has to be appended to get to the font
     *   field (Cpasjuste, why are you so inconsistent? :P)
     *
     * - "highlightify" indicates that there's a separate highlight color in the
     *   style
     */

    Helpers.TextStyle {
        id: smallStyle
        function accessor(x) { return Parser.readField(skinCfg.data, "font_small" + x); }
    }

    Helpers.TextStyle {
        id: bigStyle
        function accessor(x) { return Parser.readField(skinCfg.data, "font_big" + x); }
    }

    Helpers.TextStyle {
        id: mediaStyle
        fontify: true
        function accessor(x) { return Parser.readField(skinCfg.data, "media_text" + x); }
    }

    Helpers.TextStyle {
        id: cpuStyle
        fontify: true
        highlightify: false
        function accessor(x) { return Parser.readField(skinCfg.data, "cpu_text" + x); }
    }

    Helpers.TextStyle {
        id: sd1Style
        fontify: true
        highlightify: false
        function accessor(x) { return Parser.readField(skinCfg.data, "sd1_text" + x); }
    }

    Helpers.TextStyle {
        id: sd2Style
        fontify: true
        highlightify: false
        function accessor(x) { return Parser.readField(skinCfg.data, "sd2_text" + x); }
    }

    Helpers.TextStyle {
        id: clockStyle
        fontify: true
        highlightify: false
        function accessor(x) { return Parser.readField(skinCfg.data, "clock_text" + x); }
    }

    /*
     * Other objects: Text-related objects will have a "styleField()" method
     * that must be overridden with the correct "style.getField()" method.
     * TODO: Use property bindings instead somehow?
     */

    //Category buttons:
    Helpers.SelectionIcon {
        id: emulatorsIcon
        function accessor(x) { return Parser.readField(skinCfg.data, "emulators" + x); }
        function styleField(x) { return smallStyle.getField(x); }
        onClicked: ui.selectedIndex = 0
        intensity: emulatorsOpacity
    }

    Helpers.SelectionIcon {
        id: gamesIcon
        function accessor(x) { return Parser.readField(skinCfg.data, "games" + x); }
        function styleField(x) { return smallStyle.getField(x); }
        onClicked: ui.selectedIndex = 1
        intensity: gamesOpacity
    }

    Helpers.SelectionIcon {
        id: miscIcon
        function accessor(x) { return Parser.readField(skinCfg.data, "misc" + x); }
        function styleField(x) { return smallStyle.getField(x); }
        onClicked: ui.selectedIndex = 2
        intensity: miscOpacity
    }

    Helpers.SelectionIcon {
        id: mediaIcon
        function accessor(x) { return Parser.readField(skinCfg.data, "media" + x); }
        function styleField(x) { return smallStyle.getField(x); }
        onClicked: ui.selectedIndex = 3
        intensity: mediaOpacity
    }

    Helpers.SelectionIcon {
        id: favoritesIcon
        function accessor(x) { return Parser.readField(skinCfg.data, "favorites" + x); }
        function styleField(x) { return smallStyle.getField(x); }
        onClicked: ui.selectedIndex = 4
        intensity: favoritesOpacity
    }

    Helpers.SelectionIcon {
        id: settingsIcon
        function accessor(x) { return Parser.readField(skinCfg.data, "settings" + x); }
        function styleField(x) { return smallStyle.getField(x); }
        onClicked: ui.selectedIndex = 5
        intensity: settingsOpacity
    }

    //System info icons:
    SystemInformation {
        id: sysinfo
    }

    Helpers.PositionedImage {
        id: cpuIcon
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "cpu_icon" + x); }
    }
    Helpers.PositionedText {
        id: cpuText
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "cpu_text" + x); }
        function styleField(x) { return cpuStyle.getField(x); }
        text: (sysinfo.usedCpu * 100 / sysinfo.cpu).toFixed(2) + "%"
    }

    Helpers.PositionedImage {
        id: sd1Icon
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "sd1_icon" + x); }
    }
    Helpers.PositionedText {
        id: sd1Text
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "sd1_text" + x); }
        function styleField(x) { return sd1Style.getField(x); }
        text: (sysinfo.sd1 - sysinfo.usedSd1) + " MiB"
    }

    Helpers.PositionedImage {
        id: sd2Icon
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "sd2_icon" + x); }
    }
    Helpers.PositionedText {
        id: sd2Text
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "sd2_text" + x); }
        function styleField(x) { return sd2Style.getField(x); }
        text: (sysinfo.sd2 - sysinfo.usedSd2) + " MiB"
    }

    Helpers.PositionedImage {
        id: clockIcon
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "clock_icon" + x); }
    }
    Helpers.PositionedText {
        id: clockText
        z: 2
        function accessor(x) { return Parser.readField(skinCfg.data, "clock_text" + x); }
        function styleField(x) { return clockStyle.getField(x); }
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
    }

    //------------------------------Dynamic objects-----------------------------

    //Highlight:
    Image {
        id: highl
        z: 1
        Behavior on opacity {
            SequentialAnimation {
                //Make the highlight pulsate with a cubic curve
                //(PMenu uses a simple linear curve)
                running: true
                //repeat: true
                NumberAnimation {
                    from: 0
                    to: highlightEnabled ? 1 : 0
                    easing.type: Easing.OutCubic
                    duration: 1000
                }
                NumberAnimation {
                    from: highlightEnabled ? 1 : 0
                    to: 0
                    easing.type: Easing.InCubic
                    duration: 1000
                }
            }
        }
        source: highlight
    }

    //Dialog:
    Image {
        id: favoriteDialog
        z: 25 //Show on top of *really* EVERYTHING!
        opacity: showFavDialog ? 1 : 0
        source: Parser.readField(skinCfg.data, "confirm_box")
        x: Parser.readField(skinCfg.data, "confirm_box_x") - width / 2
        y: Parser.readField(skinCfg.data, "confirm_box_y") - height / 2
        focus: showFavDialog
        Keys.onDigit1Pressed: {
            var idf = appBrowser.currentItem.ident;
            if(ui.selectedIndex == 4) {
                var nf = favorites.value.replace(idf, "");
                nf = nf.replace("||", "|");
                favorites.value = nf.replace(/\|$|^\|/, "");
            }
            else if(favorites.value.indexOf(idf) == -1) {
                if(favorites.value.length > 0)
                    favorites.value += "|";
                favorites.value += idf;
            }
            showFavDialog = false;
        }
        Keys.onDigit2Pressed: {
            showFavDialog = false;
        }
        Text {
            anchors.centerIn: parent
            width: parent.width - 40
            height: parent.height - 20
            text: appBrowser.currentItem === null ? "" : (
                (ui.selectedIndex != 4) ? ("Do you want to add \"" + appBrowser.currentItem.friendlyName + "\" to your favorites?") :
                ("Do you want to remove \"" + appBrowser.currentItem.friendlyName + "\" from your favorites?"))
            wrapMode: Text.Wrap

            color: smallStyle.getField("color")
            font.bold: smallStyle.getField("bold")
            font.italic: smallStyle.getField("italic")
            font.pixelSize: smallStyle.getField("pixelSize")
            font.family: smallStyle.getField("family")
        }
    }

    //The settings page:
    Item {
        id: settingsPage
        x: applicationsBoxX
        y: applicationsBoxY
        z: 20 //Show on top of EVERYTHING!
        width: applicationsBoxWidth
        height: (iconScaleMin + applicationsSpacing * 0.5) * maxAppsPerPage
        opacity: settingsOpacity
        focus: ui.selectedIndex == 5

        Keys.onUpPressed: {
            if(parseInt(clockspeed.value) < 800)
                clockspeed.value = parseInt(clockspeed.value) + 10;
        }
        Keys.onDownPressed: {
            if(parseInt(clockspeed.value) > 300)
                clockspeed.value = parseInt(clockspeed.value) - 10;
        }
        Column {
            anchors.fill: parent
            Row {
                Text {
                    text: "Clockspeed: "
                    color: smallStyle.getField("highlightColor")
                    font.bold: smallStyle.getField("bold")
                    font.italic: smallStyle.getField("italic")
                    font.pixelSize: smallStyle.getField("pixelSize")
                    font.family: smallStyle.getField("family")
                }
                Text {
                    text: clockspeed.value
                    color: smallStyle.getField("color")
                    font.bold: smallStyle.getField("bold")
                    font.italic: smallStyle.getField("italic")
                    font.pixelSize: smallStyle.getField("pixelSize")
                    font.family: smallStyle.getField("family")
                }
            }
        }
    }

    Item {
        id: mediaBrowser
        z: 20 //Show on top of EVERYTHING!
        focus: !showFavDialog && (ui.selectedIndex == 3)
    }

    //The applications browser:
    Item {
        x: applicationsBoxX -5
        y: applicationsBoxY - 20
        z: 20 //Show on top of EVERYTHING!
        width: applicationsBoxWidth + 10
        height: (iconScaleMin + applicationsSpacing * 0.5) * maxAppsPerPage + 40
        clip: true
        Pandora.onPressed: {
            if(event.key == Pandora.ButtonB) {
                ui.showFavDialog = true;
                event.handled = true;
            } else if(event.key == Pandora.ButtonA) {
                Applications.execute(appBrowser.currentItem.ident);
            }
        }

        ListView {
            function determineModel(x) {
                switch(x) {
                    case 0:
                        return Applications.list.inCategory("Emulator").sortedBy("name", true);
                    case 1:
                        return Applications.list.inCategory("Game").sortedBy("name", true);
                    case 2:
                        return Applications.list.sortedBy("name", true);
                    case 4:
                        if(favorites.value.length > 0)
                            return Applications.list.matching("identifier", favorites.value).sortedBy("name", true);
                    default:
                        return Applications.list.matching("identifier", "^$") //Lists nothing
                }
            }

            id: appBrowser
            anchors.fill: parent
            anchors.topMargin: 20
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.bottomMargin: 20
            focus: !showFavDialog && (ui.selectedIndex == 0 || ui.selectedIndex == 1
                    || ui.selectedIndex == 2 || ui.selectedIndex == 4)
            model: determineModel(ui.selectedIndex)
            opacity: Math.max(emulatorsOpacity, Math.max(gamesOpacity, Math.max(miscOpacity, favoritesOpacity)))
            spacing: applicationsSpacing * 0.5
            clip: true
            Component {
                id: appHighlight
                Item {
                    y: appBrowser.currentItem.y

                    Behavior on y {
                        SpringAnimation {
                            spring: 3
                            damping: 0.2
                        }
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
                MouseArea {
                    anchors.fill: parent
                    onClicked: appBrowser.currentIndex = index
                }
                Row {
                    anchors.fill: parent
                    Image {
                        source: (icon.length > 0) ? icon : noIcon
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
                                bigStyle.getField("colorHighlight") : bigStyle.getField("color")
                            width: parent.width
                            font.bold: bigStyle.getField("bold")
                            font.italic: bigStyle.getField("italic")
                            font.pixelSize: bigStyle.getField("pixelSize")
                            font.family: bigStyle.getField("family")
                            elide: Text.ElideRight
                            text: name
                        }
                        Item {
                            height: applicationsTitleDescriptionY
                            width: parent.width
                        }
                        Text {
                            color: deleg.isCurrentItem ?
                                smallStyle.getField("colorHighlight") : smallStyle.getField("color")
                            width: parent.width
                            font.bold: smallStyle.getField("bold")
                            font.italic: smallStyle.getField("italic")
                            font.pixelSize: smallStyle.getField("pixelSize")
                            font.family: smallStyle.getField("family")
                            elide: Text.ElideRight
                            text: comment
                        }
                    }
                }
            }
        }
    }

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
            PropertyChanges {
                target: highl
                x: emulatorsIcon.x - width / 2
                y: emulatorsIcon.y - height / 2
            }
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
                x: gamesIcon.x - width / 2
                y: gamesIcon.y - height / 2
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
                x: miscIcon.x - width / 2
                y: miscIcon.y - height / 2
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
                x: mediaIcon.x - width / 2
                y: mediaIcon.y - height / 2
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
                x: favoritesIcon.x - width / 2
                y: favoritesIcon.y - height / 2
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
                x: settingsIcon.x - width / 2
                y: settingsIcon.y - height / 2
            }
        }
    ]

    transitions: [
        Transition {
            to: "settings"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    properties: "x,y"
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    duration: 200
                    properties: "settingsOpacity"
                    easing.type: Easing.Linear
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        properties: "emulatorsOpacity,gamesOpacity,miscOpacity,mediaOpacity,favoritesOpacity"
                        easing.type: Easing.OutQuad
                    }
                }
            }
        },
        Transition {
            to: "emulators"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    properties: "x,y"
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    duration: 200
                    properties: "emulatorsOpacity"
                    easing.type: Easing.Linear
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        properties: "settingsOpacity,gamesOpacity,miscOpacity,mediaOpacity,favoritesOpacity"
                        easing.type: Easing.OutQuad
                    }
                }
            }
        },
        Transition {
            to: "games"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    properties: "x,y"
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    duration: 200
                    properties: "gamesOpacity"
                    easing.type: Easing.Linear
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        properties: "settingsOpacity,emulatorsOpacity,miscOpacity,mediaOpacity,favoritesOpacity"
                        easing.type: Easing.OutQuad
                    }
                }
            }
        },
        Transition {
            to: "misc"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    properties: "x,y"
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    duration: 200
                    properties: "miscOpacity"
                    easing.type: Easing.Linear
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        properties: "settingsOpacity,gamesOpacity,emulatorsOpacity,mediaOpacity,favoritesOpacity"
                        easing.type: Easing.OutQuad
                    }
                }
            }
        },
        Transition {
            to: "media"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    properties: "x,y"
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    duration: 200
                    properties: "mediaOpacity"
                    easing.type: Easing.Linear
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        properties: "settingsOpacity,gamesOpacity,miscOpacity,emulatorsOpacity,favoritesOpacity"
                        easing.type: Easing.OutQuad
                    }
                }
            }
        },
        Transition {
            to: "favorites"
            ParallelAnimation {
                NumberAnimation {
                    duration: 300
                    properties: "x,y"
                    easing.type: Easing.OutQuad
                }
                NumberAnimation {
                    duration: 200
                    properties: "favoritesOpacity"
                    easing.type: Easing.Linear
                }
                SequentialAnimation {
                    PauseAnimation {
                        duration: 200
                    }
                    NumberAnimation {
                        duration: 300
                        properties: "settingsOpacity,gamesOpacity,miscOpacity,mediaOpacity,emulatorsOpacity"
                        easing.type: Easing.OutQuad
                    }
                }
            }
        }
    ]
}
