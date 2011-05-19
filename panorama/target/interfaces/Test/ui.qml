import Qt 4.7                   //Import Qt
import Panorama 1.0             //Import Panorama extensions
import Panorama.UI 1.0
import Panorama.Applications 1.0
import "widgets" as Widgets     //Import widgets from "widgets/"
import "pages" as Pages         //Import page prototypes from "pages/"

PanoramaUI {
    id: ui
    name: "Test"
    description: "A test Panorama UI that shows what Panorama is capable of"
    author: "dflemstr"
    anchors.fill: parent

    //Gain access to the desktop's theme colors
    SystemPalette { id: palette }

    onLoaded: { //Triggered once everything is set up
        print("Welcome to the UI named " + name + "!");
    }

    Setting { id: lastExecuted; section: "test-theme"; key: "lastExecuted" }
    Setting { id: clockspeed; section: "system"; key: "clockspeed" }

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
            Row {
                Widgets.Clock {
                    city: "Stockholm"
                    shift: 1
                }
                Column {
                    Text {
                        text: "Welcome to Panorama"
                        font.pixelSize: 32
                        font.bold: true
                        color: pages.labelColor
                        style: Text.Raised
                        styleColor: pages.labelShadowColor
                    }
                    Text {
                        text: "<p>...the ultimative alternative menu system for your OpenPandora!</p>" +
                            "<p>Some features that this release has:</p>" +
                            "<ul>" +
                            "<li>A completely dynamic interface using Javascript and QML</li>" +
                            "<li>A <em>complete</em> application loading system - conforms to" +
                            " the FDF menu specification</li>" +
                            "<li>Hardware accelerated drawing</li>" +
                            "<li>Rendering using <span style=\"color: yellow; font-weight: " +
                            "bold\">WebKit</span></li>" +
                            "<li>Touch screen navigation</li>" +
                            "<li>Instant reloading of resources - All applications and the " +
                            "'settings.cfg' file are INotified!</li>" +
                            "<li>A modular settings API that gives the UI creator absolute " +
                            "freedom</li>" +
                            "</ul>"
                        font.pixelSize: 12
                        color: pages.labelColor
                    }
                }
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom

                text: "<b>This user interface is not finished!</b><br/>" +
                    "It is only supposed to show what Panorama is capable of!"

                font.pixelSize: 24
                horizontalAlignment: Text.AlignHCenter
                color: "red"
            }
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
                appSource: Applications.list.inCategory(categoryFilter)
                    .matching("name", (nameFilter.length == 0) ? ".*" : ".*" + nameFilter + ".*")
                    .sortedBy("name", true)
                onSelected: {
                    print(identifier);
                    ui.execute(identifier);
                    lastExecuted.value = identifier;
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
                text: "<b>Clockspeed:</b> " + clockspeed.value
                color: pages.labelColor
                font.pixelSize: 24
            }
        }
    }
}
