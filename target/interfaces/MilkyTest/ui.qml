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

    state: "browse"

    states: [
        State {
            name: "browse"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
        },
        State {
            name: "sync"
            PropertyChanges { target: syncOverlay; opacity: 0.9 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
        },
        State {
            name: "categories"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.9 }
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

            color: "#99c"

            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Synchronizing database with repository..."
                font.pixelSize: ui.width / 40
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
                    "installed": { "label": "Installed", "color": "green", "installed": "true", "hasUpdate": ".*" },
                    "upgradable": { "label": "Upgradable", "color": "blue", "installed": "true", "hasUpdate": "true" }
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
                    GradientStop { position: 0.0; color: Qt.lighter(statusFilter.baseColor, 1.8) }
                    GradientStop { position: 0.8; color: Qt.lighter(statusFilter.baseColor, 1.6) }
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
                    GradientStop { position: 0.0; color: "#fff" }
                    GradientStop { position: 0.8; color: "#ccc" }
                    GradientStop { position: 1.0; color: "#aaa" }
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

        Column {
            id: buttons
            width: 120
            anchors.right: parent.right
            anchors.bottom: statusContainer.top
            anchors.top: filterContainer.bottom
            Rectangle {
                color: "lightgreen"
                width: 100
                height: 30

                Text {
                    text: "Yes"
                    anchors.centerIn: parent

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.answer(true)
                        }
                    }
                }
            }
            Rectangle {
                color: "pink"
                width: 100
                height: 30

                Text {
                    text: "No"
                    anchors.centerIn: parent

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.answer(false)
                        }
                    }
                }
            }

            Rectangle {
                color: "yellow"
                width: 100
                height: 30

                Text {
                    text: "Fail install"
                    anchors.centerIn: parent

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.install("non-existing package")
                        }
                    }
                }
            }
            Rectangle {
                color: "lightblue"
                width: 100
                height: 30

                Text {
                    text: "Install w:c"
                    anchors.centerIn: parent

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            ui.milky.install("bzar-wars-commando")
                        }
                    }
                }
            }
        }

        Rectangle {
            id: packages
            anchors.left: parent.left
            anchors.right: buttons.left
            anchors.top: toolbar.bottom
            anchors.bottom: statusContainer.top
            color: "#eee"

            Rectangle {
                id: categoryListOverlay
                anchors.fill: parent
                color: "#111"
                z: 10
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

                        color: "#00000000"
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
                    height: showDetails ? 128 : 32
                    Behavior on height { NumberAnimation { duration: 300; easing.type: Easing.OutCubic } }

                    Rectangle {
                        id: packageTitle
                        height: 32
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
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: iconImage.right
                            anchors.margins: 8
                            text: title
                            font.pixelSize: 24
                            color: "#222"
                        }

                        Rectangle {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            width: 64

                            gradient: Gradient {
                                GradientStop { position: 0; color: installed ? "#ecc" : "#cec" }
                                GradientStop { position: 1; color: installed ? "#caa" : "#aca" }
                            }

                            Text {
                                id: buttonText
                                text: installed ? "Remove" : "Install"
                                anchors.centerIn: parent
                            }
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
                        height: 96

                        Flickable {
                            anchors.fill: parent
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
