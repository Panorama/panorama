import Qt 4.6                   //Import Qt
import Panorama 1.0             //Import Panorama extensions
import "widgets" as Widgets     //Import widgets from "widgets/"
import "pages" as Pages         //Import page prototypes from "pages/"

PanoramaUI {
    id: ui
    name: "Default"
    description: "The default Panorama UI"
    author: "dflemstr"
    settingsKey: "default-theme" //The [key] that this theme gets in the config file

    //Gain access to the desktop's theme colors
    SystemPalette { id: palette }

    onLoad: { //Triggered once everything is set up
        print("Welcome to the UI named " + name + "!");
    }

    Widgets.Book {
        id: pages
        background: "images/background.png"
        anchors.fill: parent
        property color labelColor: palette.light
        property color labelShadowColor: palette.shadow
        property color labelOutlineColor: palette.text

        Widgets.Page {
            id: homePage
            width: ui.width
            height: ui.height
            title: "Home"
            icon: "images/icons/home.png"
            labelColor: pages.labelColor
            labelShadowColor: pages.labelShadowColor
            labelOutlineColor: pages.labelOutlineColor
        }

        Widgets.Page {
            id: appsPage
            width: ui.width
            height: ui.height
            title: "Applications"
            icon: "images/icons/applications.png"
            labelColor: pages.labelColor
            labelShadowColor: pages.labelShadowColor
            labelOutlineColor: pages.labelOutlineColor
            Pages.Applications {
                id: apps
                anchors.fill: parent
                highlightColor: palette.highlight
                textColor: palette.light
                appSource: ui.applications.inCategory(categoryFilter)
                    .matching("name", "*" + nameFilter + "*")
                    .sortedBy("name", true)
                onSelected: {
                    ui.execute(execLine);
                    ui.setSetting("lastExecuted", execLine);
                }
            }
        }

        Widgets.Page {
            id: settingsPage
            width: ui.width
            height: ui.height
            title: "Settings"
            icon: "images/icons/settings.png"
            labelColor: pages.labelColor
            labelShadowColor: pages.labelShadowColor
            labelOutlineColor: pages.labelOutlineColor
            Text {
                text: "Clockspeed: " + ui.sharedSetting("system", "clockspeed")
            }
        }
    }
}
