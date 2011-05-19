import Qt 4.7
import Panorama 1.0
import Panorama.UI 1.0
import Panorama.Pandora 1.0

PanoramaUI {
    id: ui
    name: "TestSuite"
    description: "A test theme that tests the Panorama-specific features"
    author: "dflemstr"
    anchors.fill: parent

    function write(what) {
        print(what.replace(/<(.|\n)*?>/g, ""));
        output.text += "<p>" + what + "</p>";
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
            Pandora.onPressed: {
                var pressed = function(key) {
                    write("Pressed the <span style\"color: yellow;\">" + key + "</span> button.");
                }
                switch(event.key) {
                case Pandora.ButtonX:
                        pressed("X");
                    break;
                case Pandora.ButtonY:
                        pressed("Y");
                    break;
                case Pandora.ButtonA:
                        pressed("A");
                    break;
                case Pandora.ButtonB:
                        pressed("B");
                    break;
                case Pandora.DPadLeft:
                        pressed("Left D-Pad");
                    break;
                case Pandora.DPadRight:
                        pressed("Right D-Pad");
                    break;
                case Pandora.DPadUp:
                        pressed("Up D-Pad");
                    break;
                case Pandora.DPadDown:
                        pressed("Down D-Pad");
                    break;
                case Pandora.TriggerL:
                        pressed("Left Trigger");
                    break;
                case Pandora.TriggerR:
                        pressed("Right Trigger");
                    break;
                case Pandora.ButtonStart:
                        pressed("Start");
                    break;
                case Pandora.ButtonSelect:
                        pressed("Select");
                    break;
                case Pandora.ButtonPandora:
                        pressed("Pandora");
                    break;
                default:
                        pressed("Unknown key " + event.key);
                }
            }

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
                        write("<span style=\"color: blue;\">Starting <span style=\"color: teal;\">" + test.name + "</span> test.</span>");
                        test.start();
                    } else {
                        write("<span style=\"color: blue;\">Stopping <span style=\"color: teal;\">" + test.name + "</span> test.</span>");
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
            text: "<style type=\"text/css\">p { margin: 0; }</style>"
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
            section: "stress"
            key: "setting1"
        }

        Setting {
            id: setting2
            section: "stress"
            key: "setting2"
        }

        Setting {
            id: setting3
            section: "stress"
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
