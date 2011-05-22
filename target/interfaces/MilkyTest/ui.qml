import Qt 4.7
import Panorama.UI 1.0
import Panorama.Milky 1.0

PanoramaUI {
    id: ui
    name: "MilkyTest"
    description: "Test UI for Milky plugin"
    author: "B-ZaR"
    anchors.fill: parent

    property QtObject milky : Milky {
        device: "/dev/loop0"
        databaseFile: "milky.db"
        logFile: "milky.log"
        targetDir: "."
        configFile: "milky.config"
    }

    Rectangle {
        anchors.fill: parent
        color: "white"

        Column
        {
            anchors.fill: parent

            Text {
                text: "Device: " + ui.milky.device
            }
            Text {
                text: "TargetDir: " + ui.milky.targetDir
            }
            Text {
                text: "DatabaseFile: " + ui.milky.databaseFile
            }
            Text {
                text: "ConfigFile: " + ui.milky.configFile
            }
            Text {
                text: "LogFile: " + ui.milky.logFile
            }
        }

    }

}
