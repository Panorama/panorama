//root.qml - The QML file that is responsible for containing PandoraUI instances
import Qt 4.7
import Panorama.Settings 1.0
import Panorama.UI 1.0

Item {
    Setting {
        id: uiDir
        section: "panorama"
        key: "uiDirectory"
        defaultValue: "interfaces"
    }
    Setting {
        id: ui
        section: "panorama"
        key: "ui"
        defaultValue: "Test"
    }
    Setting {
        id: fullscreen
        section: "panorama"
        key: "fullscreen"
        defaultValue: "false"
        onValueChanged: runtime.setFullscreen(value == "true")
    }
    Setting {
        id: dataDirectory
        section: "panorama"
        key: "dataDirectory"
    }
    Component.onCompleted: runtime.setFullscreen(fullscreen.value == "true")

    Keys.onPressed: {
        if(event.key == Qt.Key_F && event.modifiers & Qt.ControlModifier) {
            event.accepted = true;
            if(fullscreen.value == "true") {
                fullscreen.value = "false";
            }
            else {
                fullscreen.value = "true";
            }
        } else if(event.key == Qt.Key_Q && event.modifiers & Qt.ControlModifier) {
            event.accepted = true;
            Qt.quit();
        }
    }

    Loader {
        id: uiLoader
        anchors.fill: parent
        focus: true //XXX does this cause issues?
        source: "file://" + dataDirectory.value + "/" + uiDir.value + "/" + ui.value + "/ui.qml"
        onLoaded: {
            print("Loaded UI " + item.name + " created by " + item.author + ".");
            print("Description:");
            print(item.description);
        }
    }
}
