import Qt 4.7
import Panorama 1.0

PanoramaUI {
    id: ui
    name: "StressTest"
    description: "A stress test theme, testing the robustness of Panorama"
    author: "dflemstr"
    settingsSection: "stress"

    Text {
        anchors.fill: parent
        anchors.margins: 16
        text: "<p>This is a stress test suite for panorama</p>" +
                "<dl><dt>" +
                "<code>S</code> - Settings test</dt><dd>Writes to the settings " +
                "registry extremely frequently, forcing the settings to be " +
                "written to disk and flushed.</dd></dl>"
        color: "white"

        focus: true
        Keys.onPressed: {
            var test;
            if(event.key == Qt.Key_S) {
                test = settingsTest;
            }
            if(test) {
                if(!test.running) {
                    print("Starting " + test.name + " test");
                    test.start();
                } else {
                    print("Stopping " + test.name + " test");
                    test.stop();
                }
            }
        }
    }

    Item {
        id: settingsTest
        property string name: "Settings"
        property bool running: false;
        function start() {
            running = true;
        }
        function stop() {
            running = false;
            setting1.value = null;
            setting2.value = null;
            setting3.value = null;
        }

        Timer {
            id: settingsTimer
            interval: 10
            repeat: true
            running: settingsTest.running
            onTriggered: {
                setting1.value = Math.random();
                setting2.value = Math.random();
                setting3.value = Math.random();
            }
        }

        Setting {
            id: setting1
            key: "setting1"
        }

        Setting {
            id: setting2
            key: "setting2"
        }

        Setting {
            id: setting3
            key: "setting3"
        }
    }
}
