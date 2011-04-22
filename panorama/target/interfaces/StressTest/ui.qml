import Qt 4.7
import Panorama 1.0

PanoramaUI {
    id: ui
    name: "StressTest"
    description: "A stress test theme, testing the robustness of Panorama"
    author: "dflemstr"
    settingsSection: "stress"

    function write(what) {
        print(what);
        output.text += what + '\n';
    }

    Rectangle {
        color: "black"
        anchors.fill: parent
        Text {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height / 2
            anchors.margins: 16
            text: "<p>This is a stress test and feature test suite for panorama</p>" +
                    "<dl>" +
                    "<dt><code>S</code> - Settings test</dt>" +
                    "<dd>Writes to the settings registry extremely frequently, " +
                    "forcing the settings to be written to disk and flushed.</dd>" +
                    "<dt><code>F</code> - Fullscreen test</dt>" +
                    "<dd>Toggles fullscreen extremely quickly.</dd>" +
                    "<dt>Any Pandora button</dt>" +
                    "<dd>Prints to the output box the name of that button.</dd>" +
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
                case Pandora.ButtonX:
                        write("Pressed the X button");
                    break;
                case Pandora.ButtonY:
                        write("Pressed the Y button");
                    break;
                case Pandora.ButtonA:
                        write("Pressed the A button");
                    break;
                case Pandora.ButtonB:
                        write("Pressed the B button");
                    break;
                case Pandora.DPadLeft:
                        write("Pressed the Left D-Pad button");
                    break;
                case Pandora.DPadRight:
                        write("Pressed the Right D-Pad button");
                    break;
                case Pandora.DPadUp:
                        write("Pressed the Up D-Pad button");
                    break;
                case Pandora.DPadDown:
                        write("Pressed the Down D-Pad button");
                    break;
                case Pandora.TriggerL:
                        write("Pressed the Left Trigger button");
                    break;
                case Pandora.TriggerR:
                        write("Pressed the Right Trigger button");
                    break;
                case Pandora.ButtonStart:
                        write("Pressed the Start button");
                    break;
                case Pandora.ButtonSelect:
                        write("Pressed the Select button");
                    break;
                case Pandora.ButtonPandora:
                        write("Pressed the Pandora button");
                    break;
                }
                if(test) {
                    if(!test.running) {
                        write("Starting " + test.name + " test");
                        test.start();
                    } else {
                        write("Stopping " + test.name + " test");
                        test.stop();
                    }
                }
            }
        }
        Text {
            id: output
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height / 2
            anchors.margins: 16
            clip: true
            verticalAlignment: Text.AlignBottom
            text: ""
            color: "white"
        }

        Rectangle {
            anchors.fill: output
            gradient: Gradient {
                GradientStop {
                    position: 0.0
                    color: "#FF000000"
                }
                GradientStop {
                    position: 0.3
                    color: "#00000000"
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
