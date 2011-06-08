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
    }

    Column {
        id: buttons
        width: 120
        anchors.right: parent.right
        anchors.bottom: statusContainer.top
        anchors.top: parent.top
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
            color: "cyan"
            width: 100
            height: 30

            Text {
                text: "Update database"
                anchors.centerIn: parent

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        ui.milky.updateDatabase();
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
        id: info
        anchors.left: parent.left
        anchors.right: buttons.left
        anchors.bottom: statusContainer.top
        anchors.top: parent.top
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
                text: "RepositoryUrl: " + ui.milky.repositoryUrl
            }
            Text {
                text: "ConfigFile: " + ui.milky.configFile
            }
            Text {
                text: "LogFile: " + ui.milky.logFile
            }
        }

    }

    Rectangle {
        id: statusContainer
        color: "#ddd"
        height: 200
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        ListView {
            id: status
            clip: true
            anchors.fill: parent
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
                height: 20
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
