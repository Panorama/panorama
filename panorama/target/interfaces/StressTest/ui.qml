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
                "<dl>" +
                "<dt><code>S</code> - Settings test</dt>" +
                "<dd>Writes to the settings registry extremely frequently, " +
                "forcing the settings to be written to disk and flushed.</dd>" +
                "<dt><code>F</code> - Fullscreen test</dt>" +
                "<dd>Toggles fullscreen extremely quickly.</dd>" +
                "</dl>"
        color: "white"

        focus: true
        Keys.onPressed: {
            var test;
            switch(event.key) {
            case Qt.Key_S:
                    test = settingsTest;
                break;
            case Qt.Key_F:
                    test = fullscreenTest;
                break;
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

    Item {
        id: fullscreenTest
        property string name: "Fullscreen"
        property bool running: false;
        property bool previousValue: false;
        function start() {
            previousValue = fullscreenSetting.value;
            running = true;
        }
        function stop() {
            running = false;
            fullscreenSetting.value = previousValue;
        }

        Timer {
            interval: 100
            repeat: true
            running: fullscreenTest.running
            onTriggered: fullscreenSetting.value = false
        }
        Timer {
            interval: 100
            repeat: true
            running: fullscreenTest.running
            onTriggered: fullscreenSetting.value = true
        }

        Setting {
            id: fullscreenSetting
            section: "panorama"
            key: "fullscreen"
        }
    }
}
