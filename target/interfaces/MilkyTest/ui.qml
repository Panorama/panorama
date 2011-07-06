import Qt 4.7
import Panorama.UI 1.0
import Panorama.Milky 1.0
import Panorama.Settings 1.0

PanoramaUI {
    id: ui
    name: "MilkyTest"
    description: "Test UI for Milky plugin"
    author: "B-ZaR"
    anchors.fill: parent

    // ***************************************
    //                SETTINGS
    // ***************************************

    Setting {
        id: installDevice
        section: "Milky"
        key: "installDevice"
        defaultValue: "/dev/mmcblk1p1"
    }

    Setting {
        id: installDirectory
        section: "Milky"
        key: "installDirectory"
        defaultValue: "menu"
    }

    Setting {
        id: repositoryUrl
        section: "Milky"
        key: "repositoryUrl"
        defaultValue: "http://repo.openpandora.org/includes/get_data.php"
    }

    // ***************************************
    //                  MILKY
    // ***************************************

    property QtObject milky : Milky {
        device: installDevice.value
        repositoryUrl: repositoryUrl.value
        targetDir: installDirectory.value

        Component.onCompleted: {
            events.syncStart.connect(function() {
                ui.state = "sync";
            });
            events.syncDone.connect(function() {
                ui.state = "browse";
            });

        }
    }

    Item {
        focus: true
        Keys.forwardTo: [search]
    }

    function categoryHue(name) {
        var sum = 0;
        for(var i = 0; i < name.length; ++i) {
            sum += name.charCodeAt(i);
        }
        return (sum % 256) / 256.0;
    }

    // ***************************************
    //                STATES
    // ***************************************

    state: "browse"

    states: [
        State {
            name: "browse"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installDialog; opacity: 0.0 }
            PropertyChanges { target: removeDialog; opacity: 0.0 }
            PropertyChanges { target: upgradeDialog; opacity: 0.0 }
            PropertyChanges { target: previewOverlay; opacity: 0.0 }
        },
        State {
            name: "sync"
            PropertyChanges { target: syncOverlay; opacity: 0.9 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installDialog; opacity: 0.0 }
            PropertyChanges { target: removeDialog; opacity: 0.0 }
            PropertyChanges { target: upgradeDialog; opacity: 0.0 }
            PropertyChanges { target: previewOverlay; opacity: 0.0 }
        },
        State {
            name: "categories"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.9 }
            PropertyChanges { target: installDialog; opacity: 0.0 }
            PropertyChanges { target: removeDialog; opacity: 0.0 }
            PropertyChanges { target: upgradeDialog; opacity: 0.0 }
            PropertyChanges { target: previewOverlay; opacity: 0.0 }
        },
        State {
            name: "install"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installDialog; opacity: 0.9 }
            PropertyChanges { target: removeDialog; opacity: 0.0 }
            PropertyChanges { target: upgradeDialog; opacity: 0.0 }
            PropertyChanges { target: previewOverlay; opacity: 0.0 }
        },
        State {
            name: "remove"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installDialog; opacity: 0.0 }
            PropertyChanges { target: removeDialog; opacity: 0.9 }
            PropertyChanges { target: upgradeDialog; opacity: 0.0 }
            PropertyChanges { target: previewOverlay; opacity: 0.0 }
        },
        State {
            name: "upgrade"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installDialog; opacity: 0.0 }
            PropertyChanges { target: removeDialog; opacity: 0.0 }
            PropertyChanges { target: upgradeDialog; opacity: 0.9 }
            PropertyChanges { target: previewOverlay; opacity: 0.0 }
        },
        State {
            name: "preview"
            PropertyChanges { target: syncOverlay; opacity: 0.0 }
            PropertyChanges { target: categoryListOverlay; opacity: 0.0 }
            PropertyChanges { target: installDialog; opacity: 0.0 }
            PropertyChanges { target: removeDialog; opacity: 0.0 }
            PropertyChanges { target: upgradeDialog; opacity: 0.0 }
            PropertyChanges { target: previewOverlay; opacity: 0.9 }
        }

    ]

    // ***************************************
    //                TRANSITIONS
    // ***************************************

    transitions: [
        Transition { to: "browse"; NumberAnimation { properties: "opacity"; easing.type: Easing.Linear } },
        Transition { to: "categories"; NumberAnimation { properties: "opacity"; easing.type: Easing.Linear } },
        Transition { to: "install"; NumberAnimation { properties: "opacity"; easing.type: Easing.Linear } },
        Transition { to: "remove"; NumberAnimation { properties: "opacity"; easing.type: Easing.Linear } },
        Transition { to: "upgrade"; NumberAnimation { properties: "opacity"; easing.type: Easing.Linear } },
        Transition { to: "preview"; NumberAnimation { properties: "opacity"; easing.type: Easing.Linear } }
    ]


    Rectangle {
        anchors.fill: parent
        color: "black"

        // ***************************************
        //                OVERLAYS
        // ***************************************

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
            id: previewOverlay
            anchors.fill: parent
            z: 10

            property variant model

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: ui.state = "browse" }

            color: "#222"

            ListView {
                id: previewList
                property int previewSize: 500
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                height: 2*parent.height/3

                orientation: ListView.Horizontal
                snapMode: ListView.SnapToItem
                flickDeceleration: 2500

                preferredHighlightBegin: width/2 - previewSize/2
                preferredHighlightEnd: width/2 + previewSize/2
                highlightRangeMode: ListView.StrictlyEnforceRange

                cacheBuffer: width*4
                spacing: 16
                boundsBehavior: ListView.DragOverBounds

                model: parent.model

                delegate: Rectangle {
                    color: image.status == Image.Ready ? "#00000000" : "#eee"
                    height: image.status == Image.Ready ? image.height : previewList.height
                    width: previewList.previewSize
                    Behavior on height { NumberAnimation { duration: 500 } }

                    Text {
                        anchors.centerIn: parent
                        visible: image.status != Image.Ready
                        text: parseInt(image.progress * 100) + "%"
                        font.pixelSize: 24
                    }

                    Image {
                        id: image
                        source: modelData
                        width: previewList.previewSize
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }

        InstallDialog {
            id: installDialog
            anchors.fill: parent
            z: 10
            milky: ui.milky
            onActivate: ui.state = "install";
            onDeactivate: ui.state = "browse";
        }

        RemoveDialog {
            id: removeDialog
            anchors.fill: parent
            z: 10
            milky: ui.milky
            onActivate: ui.state = "remove";
            onDeactivate: ui.state = "browse";
        }

        UpgradeDialog {
            id: upgradeDialog
            anchors.fill: parent
            z: 10
            milky: ui.milky
            onActivate: ui.state = "upgrade";
            onDeactivate: ui.state = "browse";
        }

        // ***************************************
        //                TOOLBAR
        // ***************************************

        Rectangle {
            id: toolbar

            height: 48
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#ddd" }
                GradientStop { position: 0.8; color: "#aaa" }
                GradientStop { position: 1.0; color: "#888" }
            }

            Row {
                id: statusFilter
                property int selected: 0
                property string value: filterOptions[selected].value
                property variant filterOptions: [
                    { "value": "notInstalled", "label": "Browse", "baseColor": "#eee", "installed": "false", "hasUpdate": ".*" },
                    { "value": "installed", "label": "Installed", "baseColor": "#eee", "installed": "true", "hasUpdate": ".*" },
                ]

                property string label: filterOptions[selected].label
                property string installed: filterOptions[selected].installed
                property string hasUpdate: filterOptions[selected].hasUpdate

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left

                Repeater {
                    model: statusFilter.filterOptions
                    delegate: Button {
                        width: 96
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        color: modelData.baseColor
                        label: modelData.label
                        onClicked: statusFilter.selected = index;
                        pressed: statusFilter.selected == index
                    }
                }
            }

            Button {
                id: categoryFilter
                property string value: ""

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: statusFilter.right
                anchors.right: upgradeAllButton.left

                color:  Qt.hsla(ui.categoryHue(categoryFilter.value), 0.5, 0.7, 1.0)
                label: "Category: " + (categoryFilter.value ? categoryFilter.value : "All")
                onClicked: {
                    if(ui.state != "categories") {
                        ui.state = "categories";
                    } else {
                        ui.state = "browse";
                    }
                }
            }

            Button {
                id: upgradeAllButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: syncButton.left
                width: 128
                color: milky.hasUpgrades ? "#ddf" : "#888"
                enabled: milky.hasUpgrades
                label: milky.hasUpgrades ? "Upgrade all" : "No upgrades"
                onClicked: upgradeDialog.upgradeAll();
            }

            Button {
                id: syncButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: 128
                color: "#bbf"
                label: "Synchronize"
                onClicked: ui.milky.updateDatabase();
            }
        }

        // ***************************************
        //                PACKAGES
        // ***************************************

        Rectangle {
            id: packages
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: toolbar.bottom
            anchors.bottom: searchBox.top
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
                    delegate: Button {
                        width: categoryList.width / 4 - 4
                        height: 44
                        border {
                            color: "#ccc"
                            width: 2
                        }
                        textColor: "#eee"
                        font.pixelSize: 18
                        color: Qt.hsla(ui.categoryHue(edit), 0.5, 0.7, 1.0);
                        radius: 4
                        label: edit ? edit : "All"
                        onClicked: {
                            categoryFilter.value = edit;
                            ui.state = "browse"
                        }
                    }
                }
            }

            ListView {
                id: packageList
                anchors.fill: parent
                clip: true

                model: ui.milky
                  .sortedBy("title", true)
                  .sortedBy("hasUpdate", false)
                  .matching("installed", statusFilter.installed)
                  .matching("hasUpdate", statusFilter.hasUpdate)
                  .inCategory(categoryFilter.value ? categoryFilter.value : ".*")
                  .matching("title", (search.text.length > 0 && search.text.length < 3) ? "^$" : ".*" + search.text + ".*")

                cacheBuffer: height / 2

                delegate: PackageDelegate {
                    onInstall: {
                        installDialog.install(identifier, title);
                    }
                    onRemove: {
                        removeDialog.remove(identifier, title);
                    }
                    onUpgrade: {
                        upgradeDialog.upgrade(identifier, title);
                    }
                    onPreview: {
                        previewOverlay.model = previewPics;
                        ui.state = "preview";
                    }
                    onShowDetails: {
                        packageList.gotoIndex(index);
                    }
                }

                function gotoIndex(idx) {
                    var from = packageList.contentY;
                    packageList.positionViewAtIndex(idx, ListView.Contain);
                    var to = packageList.contentY;
                    scrollAnimation.from = from;
                    scrollAnimation.to = to;
                    scrollAnimation.running = true;
                }

                PropertyAnimation { id: scrollAnimation; target: packageList; property: "contentY"; duration: 200; easing.type: Easing.OutQuad }
            }

            Text {
                visible: search.text.length > 0 && packageList.count == 0
                text: search.text.length < 3 ? "At least three characters required to search" : "No packages found"
                color: "#888"
                font.pixelSize: 24
                anchors.centerIn: parent
            }

        }

        // ***************************************
        //                SEARCH
        // ***************************************

        Rectangle {
            id: searchBox
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: statusContainer.top
            height: search.text != "" ? 32 : 0
            color: "#fff"
            border.width: 2
            border.color: "#111"

            TextInput {
                id: search
                anchors.fill: parent
                anchors.leftMargin: 4
                font.pixelSize: 24
            }
        }

        // ***************************************
        //                STATUS
        // ***************************************

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
            ui.milky.events.downloadStarted.connect(createAddStatusMessageFunction("Download started."));
            ui.milky.events.downloadFinished.connect(createAddStatusMessageFunction("Download finished."));
            ui.milky.events.checkingMD5.connect(createAddStatusMessageFunction("Checking MD5..."));
            ui.milky.events.parsingFilename.connect(createAddStatusMessageFunction("Parsing filename..."));
            ui.milky.events.copyingFile.connect(createAddStatusMessageFunction("Copying file..."));
        }
    }
}
