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
        device: "/home/bzar/src/panorama/target"
        repositoryUrl: "http://repo.openpandora.org/includes/get_data.php"
        logFile: "milky.log"
        targetDir: "apps"
        configFile: "milky.config"

        Component.onCompleted: {
            events.syncStart.connect(function() {
                ui.state = "sync";
            });
            events.syncDone.connect(function() {
                ui.state = "browse";
            });

        }
    }

    function categoryHue(name) {
        var sum = 0;
        for(var i = 0; i < name.length; ++i) {
            sum += name.charCodeAt(i);
        }
        return (sum % 256) / 256.0;
    }

    state: "browse"

    states: [
        State {
            name: "browse"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installOverlay; opacity: 0.0 }
            PropertyChanges { target: removeOverlay; opacity: 0.0 }
        },
        State {
            name: "sync"
            PropertyChanges { target: syncOverlay; opacity: 0.9 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installOverlay; opacity: 0.0 }
            PropertyChanges { target: removeOverlay; opacity: 0.0 }
        },
        State {
            name: "categories"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.9 }
            PropertyChanges { target: installOverlay; opacity: 0.0 }
            PropertyChanges { target: removeOverlay; opacity: 0.0 }
        },
        State {
            name: "install"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installOverlay; opacity: 0.9 }
            PropertyChanges { target: removeOverlay; opacity: 0.0 }
        },
        State {
            name: "remove"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installOverlay; opacity: 0.0 }
            PropertyChanges { target: removeOverlay; opacity: 0.9 }
        }

    ]

    transitions: [
        Transition {
            from: "sync"
            to: "browse"
            reversible: true
            NumberAnimation {
                properties: "opacity"
                easing.type: Easing.Linear
            }
        },
        Transition {
            from: "categories"
            to: "browse"
            reversible: true
            NumberAnimation {
                properties: "opacity"
                easing.type: Easing.Linear
            }
        }
    ]


    Rectangle {
        anchors.fill: parent
        color: "black"

        Rectangle {
            id: syncOverlay
            anchors.fill: parent
            z: 10

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

            color: "#99c"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Synchronizing database with repository..."
                font.pixelSize: ui.width / 40
            }
        }

        Rectangle {
            id: installOverlay
            anchors.fill: parent
            z: 10

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

            color: "#222"

            Component.onCompleted: {
                ui.milky.events.installCheck.connect(function() {
                    ui.state = "install";
                    installOverlay.state = "verify";
                });
                ui.milky.events.installStart.connect(function() {
                    ui.state = "install";
                    installOverlay.state = "download";
                });
                ui.milky.events.downloadFinished.connect(function() {
                    ui.state = "install";
                    installOverlay.state = "apply";
                });
                ui.milky.events.installDone.connect(function() {
                    ui.state = "install";
                    installOverlay.state = "done";
                });

            }

            states: [
                State {
                    name: "verify"
                    PropertyChanges { target: installVerify; opacity: 1.0 }
                    PropertyChanges { target: installApply; opacity: 0.0 }
                    PropertyChanges { target: installDownload; opacity: 0.0 }
                    PropertyChanges { target: installDone; opacity: 0.0 }
                },
                State {
                    name: "download"
                    PropertyChanges { target: installVerify; opacity: 0.0 }
                    PropertyChanges { target: installApply; opacity: 0.0 }
                    PropertyChanges { target: installDownload; opacity: 1.0 }
                    PropertyChanges { target: installDone; opacity: 0.0 }
                },
                State {
                    name: "apply"
                    PropertyChanges { target: installVerify; opacity: 0.0 }
                    PropertyChanges { target: installDownload; opacity: 0.0 }
                    PropertyChanges { target: installApply; opacity: 1.0 }
                    PropertyChanges { target: installDone; opacity: 0.0 }
                },
                State {
                    name: "done"
                    PropertyChanges { target: installVerify; opacity: 0.0 }
                    PropertyChanges { target: installDownload; opacity: 0.0 }
                    PropertyChanges { target: installApply; opacity: 0.0 }
                    PropertyChanges { target: installDone; opacity: 1.0 }
                }
            ]

            state: "verify"

            Item {
                id: installVerify
                anchors.centerIn: parent
                height: childrenRect.height
                property string installedPackage: ""

                Text {
                    id: installVerifyLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Install PND " + parent.installedPackage + "?"
                    font.pixelSize: 24
                    color: "#eee"
                }
                Rectangle {
                    id: installYesButton
                    anchors.top: installVerifyLabel.bottom
                    anchors.right: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#cec" }
                        GradientStop { position: 1; color: "#aca" }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: "Yes"
                        font.pixelSize: 18
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.answer(true);
                        }

                    }
                }
                Rectangle {
                    id: installNoButton
                    anchors.top: installVerifyLabel.bottom
                    anchors.left: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#ecc" }
                        GradientStop { position: 1; color: "#caa" }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: "No"
                        font.pixelSize: 18
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.answer(false);
                            ui.state = "browse";
                        }
                    }
                }

            }

            Item {
                id: installDownload
                property int progress: 0
                anchors.centerIn: parent
                height: childrenRect.height

                Timer {
                    running: ui.state == "install" && installOverlay.state == "download"
                    interval: 100
                    repeat: true
                    onTriggered: {
                        if(milky.bytesToDownload) {
                            installDownload.progress = parseInt(100.0 * milky.bytesDownloaded / milky.bytesToDownload)
                        }
                    }

                }

                Text {
                    id: installDownloadLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Downloading..."
                    font.pixelSize: 24
                    color: "#eee"
                }

                Row {
                    id: installPercentageIndicator
                    anchors.top: installDownloadLabel.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.margins: 16
                    spacing: 8
                    Repeater {
                        model: 10
                        delegate: Rectangle {
                            function calcValue() {
                                if(installDownload.progress >= 10 * (index+1))
                                    return 1.0
                                else if(installDownload.progress < 10 * index)
                                    return 0.0
                                else
                                    return (installDownload.progress % 10) / 10.0
                            }

                            property real value: calcValue()

                            height: 32
                            width: 16
                            radius: 6
                            smooth: true
                            gradient: Gradient {
                                GradientStop { position: 0; color: Qt.rgba(0.5+(1.0-value)*0.5, 0.5+value*0.5, 0.5, 1.0) }
                                GradientStop { position: 1; color: Qt.rgba(0.5+(1.0-value)*0.8*0.5, 0.5+value*0.8*0.5, 0.5, 1.0) }
                            }
                        }
                    }
                }

                Text {
                    id: installPercentage

                    anchors.top: installPercentageIndicator.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.margins: 16
                    text: installDownload.progress + "%"
                    font.pixelSize: 24
                    color: "#eee"
                }

            }

            Item {
                id: installApply
                anchors.centerIn: parent
                height: childrenRect.height

                Text {
                    id: installProgressLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Applying..."
                    font.pixelSize: 24
                    color: "#eee"
                }
            }

            Item {
                id: installDone
                anchors.centerIn: parent
                height: childrenRect.height

                Text {
                    id: installDoneLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Install complete"
                    font.pixelSize: 24
                    color: "#eee"
                }
                Rectangle {
                    id: installDoneButton
                    anchors.top: installDoneLabel.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#eee" }
                        GradientStop { position: 1; color: "#ccc" }
                    }
                    Text {
                        anchors.centerIn: parent
                        text: "Continue"
                        font.pixelSize: 18
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.state = "browse";
                        }
                    }
                }
            }


        }

        Rectangle {
            id: removeOverlay
            anchors.fill: parent
            z: 10

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

            color: "#222"

            Component.onCompleted: {
                ui.milky.events.removeCheck.connect(function() {
                    ui.state = "remove";
                    removeOverlay.state = "verify";
                });
                ui.milky.events.removeStart.connect(function() {
                    ui.state = "remove";
                    removeOverlay.state = "apply";
                });
                ui.milky.events.removeDone.connect(function() {
                    ui.state = "remove";
                    removeOverlay.state = "done";
                });

            }

            states: [
                State {
                    name: "verify"
                    PropertyChanges { target: removeVerify; opacity: 1.0 }
                    PropertyChanges { target: removeApply; opacity: 0.0 }
                    PropertyChanges { target: removeDone; opacity: 0.0 }
                },
                State {
                    name: "apply"
                    PropertyChanges { target: removeVerify; opacity: 0.0 }
                    PropertyChanges { target: removeApply; opacity: 1.0 }
                    PropertyChanges { target: removeDone; opacity: 0.0 }
                },
                State {
                    name: "done"
                    PropertyChanges { target: removeVerify; opacity: 0.0 }
                    PropertyChanges { target: removeApply; opacity: 0.0 }
                    PropertyChanges { target: removeDone; opacity: 1.0 }
                }
            ]

            state: "verify"

            Item {
                id: removeVerify
                anchors.centerIn: parent
                height: childrenRect.height
                property string removedPackage: ""

                Text {
                    id: removeVerifyLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Remove PND " + parent.removedPackage + "?"
                    font.pixelSize: 24
                    color: "#eee"
                }
                Rectangle {
                    id: removeYesButton
                    anchors.top: removeVerifyLabel.bottom
                    anchors.right: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#cec" }
                        GradientStop { position: 1; color: "#aca" }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: "Yes"
                        font.pixelSize: 18
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.answer(true);
                        }

                    }
                }
                Rectangle {
                    id: removeNoButton
                    anchors.top: removeVerifyLabel.bottom
                    anchors.left: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#ecc" }
                        GradientStop { position: 1; color: "#caa" }
                    }

                    Text {
                        anchors.centerIn: parent
                        text: "No"
                        font.pixelSize: 18
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.answer(false);
                            ui.state = "browse";
                        }
                    }
                }

            }

            Item {
                id: removeApply
                anchors.centerIn: parent
                height: childrenRect.height

                Text {
                    id: removeProgressLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Removing..."
                    font.pixelSize: 24
                    color: "#eee"
                }
            }

            Item {
                id: removeDone
                anchors.centerIn: parent
                height: childrenRect.height

                Text {
                    id: removeDoneLabel
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Remove complete"
                    font.pixelSize: 24
                    color: "#eee"
                }
                Rectangle {
                    id: removeDoneButton
                    anchors.top: removeDoneLabel.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.margins: 16
                    width: 128
                    height: 48
                    gradient: Gradient {
                        GradientStop { position: 0; color: "#eee" }
                        GradientStop { position: 1; color: "#ccc" }
                    }
                    Text {
                        anchors.centerIn: parent
                        text: "Continue"
                        font.pixelSize: 18
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.state = "browse";
                        }
                    }
                }
            }


        }

        Rectangle {
            id: toolbar

            height: 48
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#eee" }
                GradientStop { position: 0.8; color: "#bbb" }
                GradientStop { position: 1.0; color: "#999" }
            }

            Rectangle {
                id: statusFilter
                property string value: "notInstalled"
                property variant filterOptions: ["notInstalled", "installed", "upgradable"]
                property variant filterProperties: {
                    "notInstalled": { "label": "Not installed", "color": "#c77", "installed": "false", "hasUpdate": ".*" },
                    "installed": { "label": "Installed", "color": "#5a5", "installed": "true", "hasUpdate": ".*" },
                    "upgradable": { "label": "Upgradable", "color": "#77c", "installed": "true", "hasUpdate": "true" }
                }

                property string label: filterProperties[value].label
                property string installed: filterProperties[value].installed
                property string hasUpdate: filterProperties[value].hasUpdate
                property color baseColor: filterProperties[value].color

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                width: 128



                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.lighter(statusFilter.baseColor, 1.6) }
                    GradientStop { position: 0.8; color: Qt.lighter(statusFilter.baseColor, 1.4) }
                    GradientStop { position: 1.0; color: Qt.lighter(statusFilter.baseColor, 1.2) }
                }

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    text: statusFilter.filterProperties[statusFilter.value].label

                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        for(var i = 0; i < statusFilter.filterOptions.length; ++i) {
                            if(statusFilter.filterOptions[i] == statusFilter.value) {
                                statusFilter.value = statusFilter.filterOptions[(i+1) % statusFilter.filterOptions.length];
                                break;
                            }
                        }
                    }
                }
            }

            Rectangle {
                id: categoryFilter

                property string value: ""

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: statusFilter.right
                width: 192

                gradient: Gradient {
                    GradientStop { position: 0.0; color: Qt.hsla(ui.categoryHue(categoryFilter.value), 0.4, 0.9, 1.0) }
                    GradientStop { position: 0.8; color: Qt.hsla(ui.categoryHue(categoryFilter.value), 0.4, 0.7, 1.0) }
                    GradientStop { position: 1.0; color: Qt.hsla(ui.categoryHue(categoryFilter.value), 0.4, 0.5, 1.0) }
                }

                Text {
                    id: categoryButton
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    text: categoryFilter.value ? categoryFilter.value : "All"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(ui.state != "categories") {
                            ui.state = "categories";
                        } else {
                            ui.state = "browse";
                        }
                    }

                }
            }

            Rectangle {
                id: syncButton

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: 128

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#ccf" }
                    GradientStop { position: 0.8; color: "#99c" }
                    GradientStop { position: 1.0; color: "#77a" }
                }

                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 18
                    text: "Synchronize"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: ui.milky.updateDatabase();

                }
            }
        }

        Rectangle {
            id: packages
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: toolbar.bottom
            anchors.bottom: statusContainer.top
            color: "#eee"

            Rectangle {
                id: categoryListOverlay
                anchors.fill: parent
                color: "#111"
                z: 10

                // Restrict mouse events to children
                MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

                GridView {
                    id: categoryList
                    anchors.fill: parent
                    model: ui.milky.categories
                    clip: true
                    cellWidth: width / 4
                    cellHeight: 48
                    delegate: Rectangle {
                        width: parent.width / 4 - 4
                        height: 44

                        border {
                            color: "#ccc"
                            width: 2
                        }

                        color: Qt.hsla(ui.categoryHue(edit), 0.4, 0.7, 1.0);
                        radius: 4

                        Text {
                            anchors.centerIn: parent
                            text: edit ? edit : "All"
                            font.pixelSize: 18
                            color: "#eee"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                categoryFilter.value = edit;
                                ui.state = "browse"
                            }

                        }
                    }

                }
            }


            ListView
            {
                anchors.fill: parent
                clip: true

                model: ui.milky
                  .sortedBy("title", true)
                  .matching("installed", statusFilter.installed)
                  .matching("hasUpdate", statusFilter.hasUpdate)
                  .inCategory(categoryFilter.value ? categoryFilter.value : ".*")

                delegate: Item {
                    id: packageItem
                    property bool showDetails: false

                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: showDetails ? 196 : 32
                    Behavior on height { NumberAnimation { duration: 300; easing.type: Easing.OutCubic } }

                    Rectangle {
                        id: packageTitle
                        height: 32
                        z: 1
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.right: parent.right
                        gradient: Gradient {
                            GradientStop { position: 0; color: installed ? "#cec" : "#eee" }
                            GradientStop { position: 1; color: installed ? "#aca" : "#ccc" }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: packageItem.showDetails = !packageItem.showDetails;
                        }
                        Image {
                            id: iconImage
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            width: 24
                            height: 24
                            source: icon
                        }

                        Text {
                            id: titleLabel
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: iconImage.right
                            anchors.margins: 8
                            text: title
                            font.pixelSize: 24
                            color: "#222"
                        }

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: titleLabel.right
                            anchors.right: parent.right
                            anchors.margins: 8
                            text: description.split("\n")[0]
                            elide: Text.ElideRight
                            font.pixelSize: 14
                            color: "#111"

                        }

                    }

                    Rectangle {
                        id: packageDetails
                        opacity: packageItem.showDetails ? 1.0 : 0
                        Behavior on opacity { NumberAnimation { duration: 300; easing.type: Easing.InOutQuad } }
                        anchors.top: packageTitle.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom

                        color: "white"

                        Flickable {
                            id: descriptionContainer
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: installButton.top

                            contentWidth: descriptionText.paintedWidth
                            contentHeight: descriptionText.paintedHeight
                            flickableDirection: Flickable.VerticalFlick
                            boundsBehavior: Flickable.StopAtBounds
                            clip: true

                            Text {
                                id: descriptionText
                                anchors.top: parent.top
                                width: packageDetails.width

                                text: description
                                color: "#222"
                                font.pixelSize: 16
                                wrapMode: Text.WordWrap
                            }
                        }

                        Rectangle {
                            id: installButton
                            anchors.bottom: parent.bottom
                            anchors.left: parent.left
                            height: 32
                            width: parent.width / 3

                            gradient: Gradient {
                                GradientStop { position: 0; color: installed ? "#ccc" : "#cec" }
                                GradientStop { position: 1; color: installed ? "#aaa" : "#aca" }
                            }

                            Text {
                                text: "Install"
                                anchors.centerIn: parent
                            }

                            MouseArea {
                                anchors.fill: parent
                                enabled: !installed
                                onClicked: ui.milky.install(identifier);
                            }
                        }
                        Rectangle {
                            id: upgradeButton
                            anchors.bottom: parent.bottom
                            anchors.left: installButton.right
                            anchors.right: removeButton.left
                            height: 32
                            width: parent.width / 3

                            gradient: Gradient {
                                GradientStop { position: 0; color: hasUpdate ? "#cce" :  "#ccc" }
                                GradientStop { position: 1; color: hasUpdate ? "#aac" :  "#aaa" }
                            }

                            Text {
                                text: "Upgrade"
                                anchors.centerIn: parent
                            }

                            MouseArea {
                                anchors.fill: parent
                                enabled: hasUpdate
                                onClicked: print("Not implemented");
                            }
                        }
                        Rectangle {
                            id: removeButton
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            height: 32
                            width: parent.width / 3

                            gradient: Gradient {
                                GradientStop { position: 0; color: installed ? "#ecc" :  "#ccc" }
                                GradientStop { position: 1; color: installed ? "#caa" :  "#aaa" }
                            }

                            Text {
                                text: "Remove"
                                anchors.centerIn: parent
                            }

                            MouseArea {
                                anchors.fill: parent
                                enabled: installed
                                onClicked: ui.milky.remove(identifier)
                            }
                        }

                    }
                }
            }

        }
        Rectangle {
            id: statusContainer

            height: 48
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#fff" }
                GradientStop { position: 0.8; color: "#ccc" }
                GradientStop { position: 1.0; color: "#aaa" }
            }

            ListView {
                id: status
                clip: true
                anchors.fill: parent
                anchors.margins: 4
                highlightFollowsCurrentItem: true

                model: ListModel {
                    id: statusMessages
                    ListElement {
                        message: "Welcome to MilkyTest!"
                    }
                }
                delegate: Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: message
                }
            }

        }

        function handleMessage(messageType, messageData) {
            var messages = {}

            messages[MilkyEvents.InvalidConfiguration] = "ERROR: Invalid configuration";
            messages[MilkyEvents.InvalidDevice] = "ERROR: Invalid device " + messageData;
            messages[MilkyEvents.DeviceNotMounted] = "ERROR: Device "  + messageData + " not mounted";
            messages[MilkyEvents.InvalidJSON] = "ERROR: Invalid JSON (" + messageData + ")";
            messages[MilkyEvents.HTTPError] = "ERROR: HTTP error (" + messageData + ")";
            messages[MilkyEvents.FileCreationError] = "ERROR: Error creating file";
            messages[MilkyEvents.FileCopyError] = "ERROR: Error copying file";
            messages[MilkyEvents.PNDNotFound] = "ERROR: PND not found (id=" + messageData + ")";
            messages[MilkyEvents.PNDNotInstalled] = "ERROR: PND not installed (id=" + messageData + ")";
            messages[MilkyEvents.PNDAlreadyInstalled] = "ERROR: PND already installed (id=" + messageData + ")";
            messages[MilkyEvents.PNDSkippingAlreadyInstalled] = "Skipping already installed PND (id=" + messageData + ")";
            messages[MilkyEvents.PNDReinstalling] = "Reinstalling PND (id=" + messageData + ")";
            messages[MilkyEvents.PNDAlreadyUpdated] = "ERROR: Already updated (id=" + messageData + ")";
            messages[MilkyEvents.PNDRemoveFailed] = "ERROR: Removing PND failed (id=" + messageData + ")";
            messages[MilkyEvents.PNDUpgradeFailed] = "ERROR: Upgrading PND failed (id=" + messageData + ")";
            messages[MilkyEvents.PNDInstallFailed] = "ERROR: Installing PND failed (id=" + messageData + ")";
            messages[MilkyEvents.PNDHasUpdate] = "PND has update (id=" + messageData + ")";
            messages[MilkyEvents.PNDFound] = "PND found (id=" + messageData + ")";
            messages[MilkyEvents.NoTargets] = "ERROR: No targets";
            messages[MilkyEvents.NoDatabase] = "No database, creating a new one";
            messages[MilkyEvents.NoUpdates] = "No updates";
            messages[MilkyEvents.MD5CheckFailed] = "ERROR: Invalid MD5 checksum";
            messages[MilkyEvents.MD5CheckFailedForce] = "ERROR: Invalid MD5 checksum, forcing";

            statusMessages.append({"message": messages[messageType]});
        }

        function createAddStatusMessageFunction(message) {
            var f = function() {
                statusMessages.append({"message": message});
                status.contentY = status.contentHeight;
            }

            return f;
        }

        Component.onCompleted: {
            ui.milky.events.message.connect(handleMessage);
            ui.milky.events.fetchStart.connect(createAddStatusMessageFunction("Fetching..."));
            ui.milky.events.fetchDone.connect(createAddStatusMessageFunction("Fetch complete."));
            ui.milky.events.syncStart.connect(createAddStatusMessageFunction("Syncing..."));
            ui.milky.events.syncDone.connect(createAddStatusMessageFunction("Sync complete."));
            ui.milky.events.saveStart.connect(createAddStatusMessageFunction("Saving..."));
            ui.milky.events.saveDone.connect(createAddStatusMessageFunction("Save complete."));
            ui.milky.events.creatingBackup.connect(createAddStatusMessageFunction("Creating backup..."));
            ui.milky.events.restoringBackup.connect(createAddStatusMessageFunction("Restoring backup..."));
            ui.milky.events.upgradeStart.connect(createAddStatusMessageFunction("Upgrading..."));
            ui.milky.events.upgradeDone.connect(createAddStatusMessageFunction("Upgrade complete."));
            ui.milky.events.upgradeCheck.connect(createAddStatusMessageFunction("Upgrade check."));
            ui.milky.events.removeStart.connect(createAddStatusMessageFunction("Removing..."));
            ui.milky.events.removeDone.connect(createAddStatusMessageFunction("Remove complete."));
            ui.milky.events.removeCheck.connect(createAddStatusMessageFunction("Remove check."));
            ui.milky.events.installStart.connect(createAddStatusMessageFunction("Installing..."));
            ui.milky.events.installDone.connect(createAddStatusMessageFunction("Install complete."));
            ui.milky.events.installCheck.connect(createAddStatusMessageFunction("Install check."));
            ui.milky.events.crawlStart.connect(createAddStatusMessageFunction("Crawling..."));
            ui.milky.events.crawlDone.connect(createAddStatusMessageFunction("Crawl complete."));
            ui.milky.events.cleanStart.connect(createAddStatusMessageFunction("Cleaning..."));
            ui.milky.events.cleanDone.connect(createAddStatusMessageFunction("Clean complete."));
            ui.milky.events.downloadFinished.connect(createAddStatusMessageFunction("Download finished."));
            ui.milky.events.checkingMD5.connect(createAddStatusMessageFunction("Checking MD5..."));
            ui.milky.events.parsingFilename.connect(createAddStatusMessageFunction("Parsing filename..."));
            ui.milky.events.copyingFile.connect(createAddStatusMessageFunction("Copying file..."));
        }
    }
}
