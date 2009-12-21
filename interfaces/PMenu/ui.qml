import Qt 4.6
import Panorama 1.0

PanoramaUI {
    id: ui
    name: "PMenu compatibility user interface"
    description: "Put this file inside of a PMenu theme to make a Panorama UI out of it!"
    author: "dflemstr"
    settingsKey: "pmenu-colors"

    TextFile { id: skinCfg; source: "skin.cfg" } //TextFile isn't standard QML, but part of Panorama 1.0

    Script {
        function readField(field) {
            var regexp = new RegExp("\\s+" + field + "\\s*=\\s*([^$]+?)\\s*;", "");
            var match = skinCfg.data.match(regexp);

            if(match != null && match.length > 1) {
                var data = match[1];
                if(data.charAt(0) == '"') {
                    data = data.substring(1, data.length - 1);
                    return data;
                }
                else if(/^-?\d+$/.test(data)) {
                    return parseInt(data);
                }
                else if(/^0x[a-fA-F0-9]{8}$/.test(data)) {
                    data = data.substring(2).toLowerCase();
                    //var a = data.substring(6, 8); //TODO: change when QML gains alpha color support
                    data = data.substring(0, 6);
                    data = "#" /*+ a*/ + data;
                    return data;
                }
                else {
                    print("Could not parse " + data);
                    return "";
                }
            }
            return null;
        }
    }

    //
    //  BEGIN PMenu compatibility properties
    //
    property string backgroundApplications: readField("background_applications")
    property string backgroundMedia: readField("background_media")
    property string backgroundSettings: readField("background_settings")

    property int applicationsBoxX: readField("applications_box_x")
    property int applicationsBoxY: readField("applications_box_y")
    property int applicationsBoxWidth: readField("applications_box_w")
    property string applicationHighlight: readField("application_highlight")

    property int iconScaleMax: readField("icon_scale_max")
    property int iconScaleMin: readField("icon_scale_min")
    property int applicationsSpacing: readField("applications_spacing")
    property int applicationsTitleDescriptionY: readField("applications_title_description_y")
    property int maxAppsPerPage: readField("max_app_per_page")

    Text { //prototype
        id: smallFontProto
        font.bold: bold
        property bool bold: ((readField("font_small_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("font_small_style") & 2) == 2)
        font.pixelSize: readField("font_small_size")
        font.family: loadFont(readField("font_small"), bold, italic)
    }
    property alias smallFont: smallFontProto.font
    property color smallFontColor: readField("font_small_color")
    property color smallFontHighlightColor: readField("font_small_color_highlight")

    Text { //prototype
        id: bigFontProto
        font.bold: bold
        property bool bold: ((readField("font_big_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("font_big_style") & 2) == 2)
        font.pixelSize: readField("font_big_size")
        font.family: loadFont(readField("font_big"), bold, italic)
    }
    property alias bigFont: bigFontProto.font
    property color bigFontColor: readField("font_big_color")
    property color bigFontHighlightColor: readField("font_big_color_highlight")

    property string confirmBox: readField("confirm_box")
    property int confirmBoxX: readField("confirm_box_x")
    property int confirmBoxY: readField("confirm_box_y")

    property int previewPicX: readField("preview_pic_x")
    property int previewPicY: readField("preview_pic_y")
    property int previewPicWidth: readField("preview_pic_w")

    property string highlight: readField("highlight")
    property bool highlightEnabled: (readField("highlight_enabled") != 0)

    property string emulatorsIcon: readField("emulators_icon")
    property string emulatorsIconHighlight: readField("emulators_icon_highlight")
    property int emulatorsIconX: readField("emulators_icon_x")
    property int emulatorsIconY: readField("emulators_icon_y")
    property string emulatorsTitle: readField("emulators_title")

    property string gamesIcon: readField("games_icon")
    property string gamesIconHighlight: readField("games_icon_highlight")
    property int gamesIconX: readField("games_icon_x")
    property int gamesIconY: readField("games_icon_y")
    property string gamesTitle: readField("games_title")

    property string miscIcon: readField("misc_icon")
    property string miscIconHighlight: readField("misc_icon_highlight")
    property int miscIconX: readField("misc_icon_x")
    property int miscIconY: readField("misc_icon_y")
    property string miscTitle: readField("misc_title")

    property string mediaIcon: readField("media_icon")
    property string mediaIconHighlight: readField("media_icon_highlight")
    property int mediaIconX: readField("media_icon_x")
    property int mediaIconY: readField("media_icon_y")
    property string mediaTitle: readField("media_title")
    property string mediaFileIcon: readField("media_file_icon")
    property string mediaFolderIcon: readField("media_folder_icon")

    Text { //prototype
        id: mediaTextFontProto
        font.bold: bold
        property bool bold: ((readField("media_text_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("media_text_style") & 2) == 2)
        font.pixelSize: readField("media_text_size")
        font.family: loadFont(readField("media_text_font"), bold, italic)
    }
    property alias mediaTextFont: mediaTextFontProto.font
    property color mediaTextFontColor: readField("media_text_color")
    property color mediaTextFontHighlightColor: readField("media_text_color_highlight")

    property int mediaMaxFilesPerPage: readField("media_max_files_per_page")

    property string favoritesIcon: readField("favorites_icon")
    property string favoritesIconHighlight: readField("favorites_icon_highlight")
    property int favoritesIconX: readField("favorites_icon_x")
    property int favoritesIconY: readField("favorites_icon_y")
    property string favoritesTitle: readField("favorites_title")

    property string settingsIcon: readField("settings_icon")
    property string settingsIconHighlight: readField("settings_icon_highlight")
    property int settingsIconX: readField("settings_icon_x")
    property int settingsIconY: readField("settings_icon_y")
    property string settingsTitle: readField("settings_title")

    property string cpuIcon: readField("cpu_icon")
    property int cpuIconX: readField("cpu_icon_x")
    property int cpuIconY: readField("cpu_icon_y")
    property int cpuTextX: readField("cpu_text_x")
    property int cpuTextY: readField("cpu_text_y")

    Text { //prototype
        id: cpuTextFontProto
        font.bold: bold
        property bool bold: ((readField("cpu_text_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("cpu_text_style") & 2) == 2)
        font.pixelSize: readField("cpu_text_size")
        font.family: loadFont(readField("cpu_text_font"), bold, italic)
    }
    property alias cpuTextFont: cpuTextFontProto.font
    property color cpuTextFontColor: readField("cpu_text_color")

    property string sd1Icon: readField("sd1_icon")
    property int sd1IconX: readField("sd1_icon_x")
    property int sd1IconY: readField("sd1_icon_y")
    property int sd1TextX: readField("sd1_text_x")
    property int sd1TextY: readField("sd1_text_y")

    Text { //prototype
        id: sd1TextFontProto
        font.bold: bold
        property bool bold: ((readField("sd1_text_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("sd1_text_style") & 2) == 2)
        font.pixelSize: readField("sd1_text_size")
        font.family: loadFont(readField("sd1_text_font"), bold, italic)
    }
    property alias sd1TextFont: sd1TextFontProto.font
    property color sd1TextFontColor: readField("sd1_text_color")

    property string sd2Icon: readField("sd2_icon")
    property int sd2IconX: readField("sd2_icon_x")
    property int sd2IconY: readField("sd2_icon_y")
    property int sd2TextX: readField("sd2_text_x")
    property int sd2TextY: readField("sd2_text_y")

    Text { //prototype
        id: sd2TextFontProto
        font.bold: bold
        property bool bold: ((readField("sd2_text_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("sd2_text_style") & 2) == 2)
        font.pixelSize: readField("sd2_text_size")
        font.family: loadFont(readField("sd2_text_font"), bold, italic)
    }
    property alias sd2TextFont: sd2TextFontProto.font
    property color sd2TextFontColor: readField("sd2_text_color")

    property string clockIcon: readField("clock_icon")
    property int clockIconX: readField("clock_icon_x")
    property int clockIconY: readField("clock_icon_y")
    property int clockTextX: readField("clock_text_x")
    property int clockTextY: readField("clock_text_y")

    Text { //prototype
        id: clockTextFontProto
        font.bold: bold
        property bool bold: ((readField("clock_text_style") & 1) == 1)
        font.italic: italic
        property bool italic: ((readField("clock_text_style") & 2) == 2)
        font.pixelSize: readField("clock_text_size")
        font.family: loadFont(readField("clock_text_font"), bold, italic)
    }
    property alias clockTextFont: clockTextFontProto.font
    property color clockTextFontColor: readField("clock_text_color")

    property bool show_categoryTitle: (readField("show_category_title") != 0)
    property string noIcon: readField("no_icon")
    property string no_preview: readField("no_preview")
    //
    //  END PMenu compatibility types
    //

    property real emusOpacity: 0
    property real gamesOpacity: 0
    property real miscOpacity: 0
    property real mediaOpacity: 0
    property real favoritesOpacity: 0
    property real settingsOpacity: 0
    property int selectedIndex: 0

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

    Script {
        function changeState(index) {
            switch(index) {
                case 0:
                    state = "emulators";
                    break;
                case 1:
                    state = "games";
                    break;
                case 2:
                    state = "misc";
                    break;
                case 3:
                    state = "media";
                    break;
                case 4:
                    state = "favorites";
                    break;
                case 5:
                    state = "settings";
            }
        }
    }
    state: "emulators"
    states: [
        State {
            name: "emulators"
            PropertyChanges {
                target: ui
                selectedIndex: 0
                emusOpacity: 1
                gamesOpacity: 0
                miscOpacity: 0
                mediaOpacity: 0
                favoritesOpacity: 0
                settingsOpacity: 0
            }
            PropertyChanges {
                target: highl
                x: emulatorsIconX - width / 2
                y: emulatorsIconY - height / 2
            }
        },
        State {
            name: "games"
            PropertyChanges {
                target: ui
                selectedIndex: 1
                emusOpacity: 0
                gamesOpacity: 1
                miscOpacity: 0
                mediaOpacity: 0
                favoritesOpacity: 0
                settingsOpacity: 0
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
                emusOpacity: 0
                gamesOpacity: 0
                miscOpacity: 1
                mediaOpacity: 0
                favoritesOpacity: 0
                settingsOpacity: 0
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
                emusOpacity: 0
                gamesOpacity: 0
                miscOpacity: 0
                mediaOpacity: 1
                favoritesOpacity: 0
                settingsOpacity: 0
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
                emusOpacity: 0
                gamesOpacity: 0
                miscOpacity: 0
                mediaOpacity: 0
                favoritesOpacity: 1
                settingsOpacity: 0
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
                emusOpacity: 0
                gamesOpacity: 0
                miscOpacity: 0
                mediaOpacity: 0
                favoritesOpacity: 0
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

    //Backgrounds:
    Image {
        id: appsBackground
        z: -10
        opacity: Math.max(emusOpacity, Math.max(gamesOpacity, Math.max(miscOpacity, favoritesOpacity)))
        anchors.fill: parent
        source: backgroundApplications
    }
    Image {
        id: mediaBackground
        z: -10
        opacity: mediaOpacity
        anchors.fill: parent
        source: backgroundMedia
    }
    Image {
        id: settingsBackground
        z: -10
        opacity: settingsOpacity
        anchors.fill: parent
        source: backgroundSettings
    }

    //Highlight:
    Image {
        id: highl
        z: -5
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

    //Emulators:
    Image {
        id: emulatorsBtn
        source: emulatorsIcon
        x: emulatorsIconX - width / 2
        y: emulatorsIconY - height / 2
        opacity: 1 - emusOpacity
        MouseRegion {
            anchors.fill: parent
            onPressed: { ui.state = "emulators" }
        }
    }
    Text {
        anchors.top: emulatorsBtn.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: emulatorsBtn.horizontalCenter
        text: emulatorsTitle
        color: smallFontColor
        font.bold: smallFont.bold
        font.italic: smallFont.italic
        font.pixelSize: smallFont.pixelSize
        font.family: smallFont.family
    }
    Image {
        id: emulatorsBtnHighlight
        source: emulatorsIconHighlight
        x: emulatorsIconX - width / 2
        y: emulatorsIconY - height / 2
        opacity: emusOpacity
    }

    //Games:
    Image {
        id: gamesBtn
        source: gamesIcon
        x: gamesIconX - width / 2
        y: gamesIconY - height / 2
        opacity: 1 - gamesOpacity
        MouseRegion {
            anchors.fill: parent
            onPressed: { ui.state = "games" }
        }
    }
    Text {
        anchors.top: gamesBtn.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: gamesBtn.horizontalCenter
        text: gamesTitle
        color: smallFontColor
        font.bold: smallFont.bold
        font.italic: smallFont.italic
        font.pixelSize: smallFont.pixelSize
        font.family: smallFont.family
    }
    Image {
        id: gamesBtnHighlight
        source: gamesIconHighlight
        x: gamesIconX - width / 2
        y: gamesIconY - height / 2
        opacity: gamesOpacity
    }

    //Misc:
    Image {
        id: miscBtn
        source: miscIcon
        x: miscIconX - width / 2
        y: miscIconY - height / 2
        opacity: 1 - miscOpacity
        MouseRegion {
            anchors.fill: parent
            onPressed: { ui.state = "misc" }
        }
    }
    Text {
        anchors.top: miscBtn.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: miscBtn.horizontalCenter
        text: miscTitle
        color: smallFontColor
        font.bold: smallFont.bold
        font.italic: smallFont.italic
        font.pixelSize: smallFont.pixelSize
        font.family: smallFont.family
    }
    Image {
        id: miscBtnHighlight
        source: miscIconHighlight
        x: miscIconX - width / 2
        y: miscIconY - height / 2
        opacity: miscOpacity
    }

    //Media:
    Image {
        id: mediaBtn
        source: mediaIcon
        x: mediaIconX - width / 2
        y: mediaIconY - height / 2
        opacity: 1 - mediaOpacity
        MouseRegion {
            anchors.fill: parent
            onPressed: { ui.state = "media" }
        }
    }
    Text {
        anchors.top: mediaBtn.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: mediaBtn.horizontalCenter
        text: mediaTitle
        color: smallFontColor
        font.bold: smallFont.bold
        font.italic: smallFont.italic
        font.pixelSize: smallFont.pixelSize
        font.family: smallFont.family
    }
    Image {
        id: mediaBtnHighlight
        source: mediaIconHighlight
        x: mediaIconX - width / 2
        y: mediaIconY - height / 2
        opacity: mediaOpacity
    }

    //Favorites:
    Image {
        id: favoritesBtn
        source: favoritesIcon
        x: favoritesIconX - width / 2
        y: favoritesIconY - height / 2
        opacity: 1 - favoritesOpacity
        MouseRegion {
            anchors.fill: parent
            onPressed: { ui.state = "favorites" }
        }
    }
    Text {
        anchors.top: favoritesBtn.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: favoritesBtn.horizontalCenter
        text: favoritesTitle
        color: smallFontColor
        font.bold: smallFont.bold
        font.italic: smallFont.italic
        font.pixelSize: smallFont.pixelSize
        font.family: smallFont.family
    }
    Image {
        id: favoritesBtnHighlight
        source: favoritesIconHighlight
        x: favoritesIconX - width / 2
        y: favoritesIconY - height / 2
        opacity: favoritesOpacity
    }

    //Settings:
    Image {
        id: settingsBtn
        source: settingsIcon
        x: settingsIconX - width / 2
        y: settingsIconY - height / 2
        opacity: 1 - settingsOpacity
        MouseRegion {
            anchors.fill: parent
            onPressed: { ui.state = "settings" }
        }
    }
    Text {
        anchors.top: settingsBtn.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: settingsBtn.horizontalCenter
        text: settingsTitle
        color: smallFontColor
        font.bold: smallFont.bold
        font.italic: smallFont.italic
        font.pixelSize: smallFont.pixelSize
        font.family: smallFont.family
    }
    Image {
        id: settingsBtnHighlight
        source: settingsIconHighlight
        x: settingsIconX - width / 2
        y: settingsIconY - height / 2
        opacity: settingsOpacity
    }

    Image {
        source: clockIcon
        x: clockIconX
        y: clockIconY
    }
    Item {
        id: clockAnchor
        y: clockTextY
    }
    Text {
        x: clockTextX
        anchors.baseline: clockAnchor.top
        font.family: clockTextFont.family
        font.bold: clockTextFont.bold
        font.italic: clockTextFont.italic
        font.pixelSize: clockTextFont.pixelSize
        color: clockTextFontColor
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

    Image {
        source: sd1Icon
        x: sd1IconX
        y: sd1IconY
    }
    Item {
        id: sd1Anchor
        y: sd1TextY
    }
    Text {
        x: sd1TextX
        anchors.baseline: sd1Anchor.top
        font.bold: sd1TextFont.bold
        font.italic: sd1TextFont.italic
        font.pixelSize: sd1TextFont.pixelSize
        color: sd1TextFontColor
        text: "1024 MiB"
    }

    Image {
        source: sd2Icon
        x: sd2IconX
        y: sd2IconY
    }
    Item {
        id: sd2Anchor
        y: sd2TextY
    }
    Text {
        x: sd2TextX
        anchors.baseline: sd2Anchor.top
        font.bold: sd2TextFont.bold
        font.italic: sd2TextFont.italic
        font.pixelSize: sd2TextFont.pixelSize
        color: sd2TextFontColor
        text: "1024 MiB"
    }

    Image {
        source: cpuIcon
        x: cpuIconX
        y: cpuIconY
    }
    Item {
        id: cpuAnchor
        y: cpuTextY
    }
    Text {
        x: cpuTextX
        anchors.baseline: cpuAnchor.top
        font.bold: cpuTextFont.bold
        font.italic: cpuTextFont.italic
        font.pixelSize: cpuTextFont.pixelSize
        color: cpuTextFontColor
        text: settingsPage.clockspeed
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
        focus: (ui.selectedIndex == 3)
    }

    //The applications browser:
    Item {
        x: applicationsBoxX -5
        y: applicationsBoxY - 20
        width: applicationsBoxWidth + 10
        height: (iconScaleMin + applicationsSpacing * 0.5) * maxAppsPerPage + 40
        clip: true
        Keys.onDigit2Pressed: { //The rightmost Pandora button
            var favorites = sharedSetting("system", "favorites");
            var exec = appBrowser.currentItem.execLine;
            if(favorites.indexOf(exec) == -1) {
                if(favorites.length > 0)
                    favorites += "|";
                favorites += exec;
                setSharedSetting("system", "favorites", favorites);
            }
        }
        Keys.onDigit1Pressed: {
            execute(appBrowser.currentItem.execLine);
        }
        ListView {
            id: appBrowser
            anchors.fill: parent
            anchors.topMargin: 20
            anchors.leftMargin: 5
            anchors.rightMargin: 5
            anchors.bottomMargin: 20
            focus: (ui.selectedIndex == 0 || ui.selectedIndex == 1 || ui.selectedIndex == 2 || ui.selectedIndex == 4)
            model: (ui.selectedIndex == 0) ? ui.applications.inCategory("Emulator").sortedBy("name", true)
                 : (ui.selectedIndex == 1) ? ui.applications.inCategory("Game").sortedBy("name", true)
                 : (ui.selectedIndex == 2) ? ui.applications.inCategory("^(?!Game|Emulator)$").sortedBy("name", true)
                 : (ui.selectedIndex == 4) ? ui.applications.matching("exec", sharedSetting("system", "favorites")).sortedBy("name", true)
                 : ui.applications.matching("exec", "^$") //Lists nothing

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
                property string execLine: exec
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
                            text: name
                        }
                        Text {
                            color: deleg.isCurrentItem ?
                                ui.smallFontColorHighlight : ui.smallFontColor
                            font.bold: smallFont.bold
                            font.italic: smallFont.italic
                            font.pixelSize: smallFont.pixelSize
                            font.family: smallFont.family
                            text: name
                        }
                    }
                }
            }
        }
    }
}
