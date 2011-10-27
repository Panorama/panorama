import Qt 4.7
import Panorama.UI 1.0
import Panorama.Milky 1.0
import Panorama.Settings 1.0
import Panorama.Pandora 1.0
import Panorama.Applications 1.0

PanoramaUI {
    id: ui
    name: "Consolidation"
    description: "Console style composite UI for package management and application launching"
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
        id: repositoryUrls
        section: "Milky"
        key: "repositoryUrls"
        defaultValue: "http://repo.openpandora.org/includes/get_data.php"
    }

    Setting {
        id: customDevices
        section: "Milky"
        key: "customDevices"
        defaultValue: ""
    }

    Setting {
        id: minimumSearchQueryLength
        section: "Consolidation"
        key: "minimumSearchQueryLength"
        defaultValue: 3
    }

    // Run stuff when the entire UI is loaded
    Timer {
        interval: 1
        running: true
        repeat: false
        onTriggered: {
            ui.milky.crawlDevice();
        }
    }

    Timer {
        interval: 300000
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            syncButton.updateEnabled();
        }
    }

    // ***************************************
    //                CONTROLS
    // ***************************************

    Item {
        focus: true
        Keys.forwardTo: [hotKeyHandler, search]
    }

    Item {
        id: hotKeyHandler
        Keys.onPressed: {
            var accept = true;
            if(ui.state == "browse") {
                var item = packageList.currentItem;
                switch(event.key) {
                    case Qt.Key_Up:
                        packageList.up();
                        break;
                    case Qt.Key_Down:
                        packageList.down();
                        break;
                    case Qt.Key_Left:
                        packageList.pageUp();
                        break;
                    case Qt.Key_Right:
                        packageList.pageDown();
                        break;
                    default:
                        accept = false;
                }
            } else if(ui.state == "preview") {
                var item = packageList.currentItem;
                switch(event.key) {
                    case Qt.Key_Return:
                        ui.setState("details")
                        break;
                    default:
                        accept = false;
                }
            } else if(ui.state == "details") {
                switch(event.key) {
                    case Qt.Key_Return:
                        detailDialog.preview();
                        break;
                    default:
                        accept = false;
                }
            } else if(ui.state == "applications") {
                switch(event.key) {
                    case Qt.Key_Up:
                        applications.moveCurrentIndexUp();
                        break;
                    case Qt.Key_Down:
                        applications.moveCurrentIndexDown();
                        break;
                    case Qt.Key_Left:
                        applications.moveCurrentIndexLeft();
                        break;
                    case Qt.Key_Right:
                        applications.moveCurrentIndexRight();
                        break;
                    case Qt.Key_Return:
                        applications.executeCurrentItem();
                        break;
                    default:
                        accept = false;
                }
            } else{
                accept = false;
            }

            event.accepted = accept;
        }
    }

    Pandora.onPressed: {
        var accept = true;
        if(ui.state == "browse") {
            var item = packageList.currentItem;
            switch(event.key) {
                case Pandora.ButtonB:
                    item.showDetails()
                    break;
                case Pandora.TriggerL:
                    modeButton.clicked(false);
                    break;
                case Pandora.TriggerR:
                    ui.setState("categories");
                    break;
                case Pandora.ButtonStart:
                    syncButton.clicked(false);
                    break;
                case Pandora.ButtonSelect:
                    if(upgradeAllButton.enabled)
                        upgradeAllButton.clicked(false);
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "categories") {
            switch(event.key) {
                case Pandora.DPadUp:
                    categoryListOverlay.categoryList.moveCurrentIndexUp();
                    break;
                case Pandora.DPadDown:
                    categoryListOverlay.categoryList.moveCurrentIndexDown();
                    break;
                case Pandora.DPadLeft:
                    categoryListOverlay.categoryList.moveCurrentIndexLeft();
                    break;
                case Pandora.DPadRight:
                    categoryListOverlay.categoryList.moveCurrentIndexRight();
                    break;
                case Pandora.ButtonB:
                    categoryListOverlay.categoryList.currentItem.clicked(false);
                    break;
                case Pandora.TriggerL:
                    modeButton.clicked(false);
                    break;
                case Pandora.TriggerR:
                    categoryFilter.clicked(false);
                    break;
                case Pandora.ButtonStart:
                    syncButton.clicked(false);
                    break;
                case Pandora.ButtonSelect:
                    if(upgradeAllButton.enabled)
                        upgradeAllButton.clicked(false);
                    break;
                case Pandora.ButtonY:
                    categoryFilter.nextOrder();
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "install") {
            switch(event.key) {
                case Pandora.ButtonB:
                    installDialog.yes();
                    break;
                case Pandora.ButtonX:
                    installDialog.no()
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "remove") {
            switch(event.key) {
                case Pandora.ButtonB:
                    removeDialog.yes();
                    break;
                case Pandora.ButtonX:
                    removeDialog.no()
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "upgrade") {
            switch(event.key) {
                case Pandora.ButtonB:
                    upgradeDialog.yes();
                    break;
                case Pandora.ButtonX:
                    upgradeDialog.no()
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "preview") {
            switch(event.key) {
                case Pandora.DPadLeft:
                    previewList.decrementCurrentIndex();
                    break;
                case Pandora.DPadRight:
                    previewList.incrementCurrentIndex();
                    break;
                case Pandora.ButtonX:
                    state = "details";
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "details") {
            var item = packageList.currentItem;
            switch(event.key) {
                case Pandora.ButtonX:
                    ui.back();
                    break;
                case Pandora.ButtonB:
                    if(!item.isInstalled) detailDialog.install();
                    break;
                case Pandora.ButtonA:
                    if(item.isInstalled) detailDialog.remove();
                    break;
                case Pandora.ButtonY:
                    if(item.hasUpgrade) detailDialog.upgrade();
                    break;
                default:
                    accept = false;
            }
        } else if(ui.state == "applications") {
            switch(event.key) {

                case Pandora.ButtonB:
                    applications.executeCurrentItem();
                    break;
                case Pandora.ButtonY:
                    applications.showCurrentItemDetails();
                    break;
                case Pandora.TriggerL:
                    modeButton.clicked(false);
                    break;
                case Pandora.TriggerR:
                    ui.setState("categories");
                    break;
                case Pandora.ButtonStart:
                    syncButton.clicked(false);
                    break;
                case Pandora.ButtonSelect:
                    if(upgradeAllButton.enabled)
                        upgradeAllButton.clicked(false);
                    break;
                default:
                    accept = false;
            }
        }
        event.accepted = accept;
    }

    // ***************************************
    //                  MILKY
    // ***************************************

    property QtObject milky : Milky {
        device: installDevice.value
        targetDir: installDirectory.value

        Component.onCompleted: {
            events.syncStart.connect(function() {
                ui.setState("sync");
            });
            events.syncDone.connect(function() {
                ui.setState("browse");
                syncButton.updateEnabled();
            });

            if(typeof(repositoryUrls.value) == "string" && repositoryUrls.value.length != 0) {
               milky.addRepository(repositoryUrls.value);
            } else {
                for(var i = 0; i < repositoryUrls.value.length; ++i) {
                    milky.addRepository(repositoryUrls.value[i]);
                }
            }
        }
    }

    // ***************************************
    //                STATES
    // ***************************************

    state: "applications"
    property string previousState: "applications"

    function setState(newState) {
        previousState = state;
        state = newState;
    }

    function back() {
        var temp = state;
        state = previousState;
        previousState = temp;
    }

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
            visible: ui.state == "sync"

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

            color: Qt.rgba(0.4,0.4,0.7,0.9)

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
            visible: ui.state == "preview"

            property variant model

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: ui.setState("details") }

            color: Qt.rgba(0.1,0.1,0.1,0.8)

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

        Rectangle {
            id: detailOverlay
            anchors.fill: parent
            z: 10
            visible: ui.state == "details"

            // Restrict mouse events to children
            MouseArea { anchors.fill: parent; onPressed: ui.setState("browse") }

            color: Qt.rgba(0.1,0.1,0.1,0.8)

            PackageDetails {
                id: detailDialog
                anchors.fill: parent
                anchors.margins: 64
                milky: ui.milky

                onInstall: {
                    installDialog.install(pnd.id, pnd.title);
                }
                onRemove: {
                    removeDialog.remove(pnd.id, pnd.title);
                }
                onUpgrade: {
                    upgradeDialog.upgrade(pnd.id, pnd.title);
                }
                onPreview: {
                    previewOverlay.model = pnd.previewPics;
                    ui.setState("preview");
                }
                onBack: {
                    ui.setState("browse");
                }
            }
        }

        InstallDialog {
            id: installDialog
            visible: active
            anchors.fill: parent
            z: 10
            milky: ui.milky
            installDirectorySetting: installDirectory
            onActivate: ui.setState("install");
            onDeactivate: ui.setState("browse");
        }

        RemoveDialog {
            id: removeDialog
            visible: ui.state == "remove"
            anchors.fill: parent
            z: 10
            milky: ui.milky
            onActivate: ui.setState("remove");
            onDeactivate: ui.setState("browse");
        }

        UpgradeDialog {
            id: upgradeDialog
            visible: ui.state == "upgrade"
            anchors.fill: parent
            z: 10
            milky: ui.milky
            onActivate: ui.setState("upgrade");
            onDeactivate: ui.back();
        }

        // ***************************************
        //                TOOLBAR
        // ***************************************

        Rectangle {
            id: toolbar
            z: 50
            height: 48
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#ddd" }
                GradientStop { position: 0.8; color: "#aaa" }
                GradientStop { position: 1.0; color: "#888" }
            }

            Button {
                id: modeButton
                width: 110
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                label: ui.state == "applications" ? "Install" : "Launch"
                controlHint: "L"
                onClicked: {
                    if(ui.state == "applications") {
                        ui.setState("browse");
                        packageList.updateModel();
                    } else {
                        ui.setState("applications");
                        applications.updateModel();
                    }
                }
            }
            Button {
                id: categoryFilter
                property string value: ""

                property int selectedOrder: 0
                property variant orderOptions: [
                    {title:"Alphabetical", value:"title", ascending: true, sectionProperty: "", sectionCriteria: -1},
                    {title:"Newest", value:"modified", ascending: false, sectionProperty: "lastUpdatedString", sectionCriteria: ViewSection.FullString}
                ]

                property string orderTitle: orderOptions[selectedOrder].title
                property string orderProperty: orderOptions[selectedOrder].value
                property bool orderAscending: orderOptions[selectedOrder].ascending
                property string sectionProperty: orderOptions[selectedOrder].sectionProperty
                property int sectionCriteria: orderOptions[selectedOrder].sectionCriteria

                function nextOrder() {
                    selectedOrder = (selectedOrder + 1) % orderOptions.length;
                }

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: modeButton.right
                anchors.right: upgradeAllButton.left

                color: "#ddf"
                label: (categoryFilter.value ? categoryFilter.value : "All") + ", " + orderTitle
                controlHint: "R"
                onClicked: {
                    if(ui.state != "categories") {
                        ui.setState("categories");
                    } else {
                        ui.back();
                        if(ui.state == "applications") {
                            applications.updateModel()
                        } else {
                            packageList.updateModel()
                        }
                    }
                }
            }

            Button {
                id: upgradeAllButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: syncButton.left
                width: 160
                color: enabled ? "#ddf" : "#888"
                enabled: milky.hasUpgrades
                label: enabled ? "Upgrade all" : "No upgrades"
                controlHint: enabled ? "Sl" : ""
                onClicked: upgradeDialog.upgradeAll();
            }

            Button {
                id: syncButton
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                width: 160
                color: enabled ? "#bbf" : "#888"
                label: enabled ? "Synchronize" : "Up to date"
                controlHint: enabled ? "St" : ""
                onClicked: ui.milky.syncWithRepository();

                function updateEnabled() {
                    var updated = ui.milky.repositoryUpdated();
                    var lastSynced = 0;
                    var repositories = ui.milky.repositories;
                    for(var i = 0; i < repositories.length; ++i) {
                        var timestamp = new Date(repositories[i].timestamp).getTime();
                        lastSynced = lastSynced > timestamp ? lastSynced : timestamp;
                    }

                    var neverSynced = lastSynced == 0;
                    enabled = updated || neverSynced;
                }
            }
        }

        Rectangle {
            id: topSeparator
            z: 50
            height: 4
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: toolbar.bottom
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#888" }
                GradientStop { position: 1.0; color: "#666" }
            }

        }

        Item {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: topSeparator.bottom
            anchors.bottom: searchBox.top

            // ***************************************
            //             APPLICATIONS
            // ***************************************

            Rectangle {
                id: applicationsContainer
                anchors.fill: parent
                visible: ui.state == "applications"

                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#555" }
                    GradientStop { position: 1.0; color: "#333" }
                }

                GridView {
                    id: applications
                    anchors.fill: parent

                    property int rowSize: 8
                    property real spacing: 8

                    property int textSize: 12
                    property int iconSize: Math.floor((cellHeight - textSize) / 16) * 16

                    function updateModel() {
                        model = filteredModel();
                    }

                    function filteredModel() {
                        var result = Applications.list;

                        if(categoryFilter.value)
                            result = result.inCategory(categoryFilter.value)

                        if(search.text)
                            result = result.matching("title", ".*" + search.text + ".*")

                        return result.sortedBy("name", true);
                    }

                    function executeCurrentItem() {
                        console.log(applications.currentItem.ident)
                        Applications.execute(applications.currentItem.ident);
                    }

                    function showCurrentItemDetails() {
                        console.log("*** pndId:" + applications.currentItem.pndId);
                        if(applications.currentItem.pndId) {
                            detailDialog.pndId = applications.currentItem.pndId;
                            detailDialog.application = applications.currentItem;
                            ui.setState("details");
                        }
                    }

                    model: []

                    Component.onCompleted: updateModel();

                    cellWidth: width / rowSize
                    cellHeight: cellWidth

                    cacheBuffer: height*4

                    highlightFollowsCurrentItem: false

                    highlight: Rectangle {
                        x: applications.currentItem.x
                        y: applications.currentItem.y
                        color: "#888"
                        radius: width/8
                        width: applications.cellWidth
                        height: applications.cellWidth
                    }

                    delegate: Item {
                        property string ident: identifier
                        property string pndId: pandoraId
                        width: applications.cellWidth
                        height: applications.cellHeight
                        Item {
                            anchors.fill: parent
                            anchors.margins: applications.spacing / 2

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    applications.currentIndex = index;
                                }
                                onDoubleClicked: {
                                    applications.executeCurrentItem();
                                }
                            }
                            Image {
                                id: iconField
                                source: icon ? icon : "images/application-x-executable.png"
                                height: applications.iconSize
                                width: applications.iconSize
                                sourceSize.width: applications.iconSize
                                asynchronous: true
                                smooth: false
                                anchors.top: parent.top
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                            Text {
                                id: nameLabel

                                width: parent.width

                                text: name
                                font.pixelSize: applications.textSize
                                font.bold: true
                                style: Text.Outline; styleColor: "#222"
                                color: "#ddd"

                                anchors.fill: parent
                                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignBottom
                            }
                        }
                    }
                }
            }

            // ***************************************
            //                PACKAGES
            // ***************************************


            Rectangle {
                id: packages
                anchors.fill: parent
                color: "#eee"
                visible: ui.state != "applications"

                ListView {
                    id: packageList
                    anchors.fill: parent
                    currentIndex: 0

                    function up() {
                        decrementCurrentIndex();
                        positionViewAtIndex(currentIndex, ListView.Contain);
                    }
                    function down() {
                        incrementCurrentIndex();
                        positionViewAtIndex(currentIndex, ListView.Contain);
                    }
                    function pageUp() {
                        gotoIndex(currentIndex < 10 ? 0 : currentIndex - 10, ListView.Beginning);
                    }
                    function pageDown() {
                        if(model.numResults === undefined)
                            return;
                        gotoIndex(currentIndex + 10 < model.numResults() ? currentIndex + 10 : model.numResults() - 1, ListView.Beginning);
                    }

                    function updateModel() {
                        model = filteredModel();
                    }

                    function filteredModel() {
                        if(search.text.length > 0 && search.text.length < minimumSearchQueryLength.value)
                            return [];

                        var result = ui.milky.matching("installed", false);

                        if(categoryFilter.value)
                            result = result.inCategory(categoryFilter.value)

                        if(search.text)
                            result = result.matching("title", ".*" + search.text + ".*")

                        return result.sortedBy(categoryFilter.orderProperty, categoryFilter.orderAscending).sortedBy("hasUpdate", false);
                    }

                    model: []

                    Component.onCompleted: updateModel();

                    cacheBuffer: 2 * height

                    highlightFollowsCurrentItem: false
                    highlight: Rectangle {
                        z: 10
                        y: packageList.currentItem.y
                        height: 32
                        width: packageList.currentItem.width
                        gradient: Gradient {
                            GradientStop { position: 0.0; color: Qt.rgba(0.8,0.6,0.8,0.1) }
                            GradientStop { position: 0.7; color: Qt.rgba(0.8,0.6,0.8,0.3) }
                            GradientStop { position: 1.0; color: Qt.rgba(0.8,0.6,0.8,0.8) }
                        }
                    }

                    delegate: PackageDelegate {
                        onShowDetails: {
                            detailDialog.pndId = identifier;
                            packageList.currentIndex = index;
                            ui.setState("details");
                        }
                    }


                    section.property: categoryFilter.sectionProperty
                    section.criteria: categoryFilter.sectionCriteria
                    section.delegate: Rectangle {
                        height: 32
                        width: packageList.width
                        z: 10
                        color: "#555"

                        Text {
                            anchors.leftMargin: 16
                            anchors.fill: parent
                            text: section
                            font.pixelSize: 24
                            color: "#eee"
                        }
                    }

                    function gotoIndex(idx, mode) {
                        scrollAnimation.stop();
                        var from = packageList.contentY;
                        packageList.positionViewAtIndex(idx, mode);
                        var to = packageList.contentY;
                        currentIndex = idx;
                        scrollAnimation.from = from;
                        scrollAnimation.to = to;
                        scrollAnimation.start();
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

            FilterDialog {
                id: categoryListOverlay
                z: 10
                anchors.fill: parent
                visible: ui.state == "categories"
                categoryFilter: categoryFilter
                model: ui.milky.categories
            }
        }
        // ***************************************
        //             ACTION QUEUE
        // ***************************************
        Rectangle {
            id: actionQueueContainer

            property int minWidth: 64
            property int maxWidth: 256
            property int thresholdWidth: 128
            property int xMin: parent.width - maxWidth
            property int xMax: parent.width - minWidth
            property int xHidden: parent.width

            property bool hidden: true
            property bool large: true

            z: 50
            x: xHidden

            //anchors.right: parent.right
            anchors.top: topSeparator.bottom
            anchors.bottom: searchBox.top
            width: parent.width - x
            clip: true

            color: "#111"

            PropertyAnimation {
                id: actionQueueContainerAnimation
                target: actionQueueContainer
                property: "x"
                duration: 200
            }

            MouseArea {
                anchors.fill: parent
                drag {
                    target: actionQueueContainer
                    axis: Drag.XAxis
                    minimumX: parent.xMin
                    maximumX: parent.xMax
                    filterChildren: true
                }
                onReleased: {
                    actionQueueContainerAnimation.stop();
                    actionQueueContainerAnimation.from = drag.target.x;
                    if(drag.target.width > parent.thresholdWidth) {
                        actionQueueContainerAnimation.to = parent.xMin;
                        drag.target.large = true;
                    } else {
                        actionQueueContainerAnimation.to = parent.xMax;
                        drag.target.large = false;
                    }
                    actionQueueContainerAnimation.start();
                }

                ActionQueue {
                    id: actionQueue
                    anchors.fill: parent
                    milky: ui.milky

                    onItemAdded: {
                        if(actionQueueContainer.hidden) {
                            actionQueueContainerAnimation.stop();
                            actionQueueContainer.hidden = false;
                            actionQueueContainerAnimation.from = actionQueueContainer.xHidden;
                            if(actionQueueContainer.large) {
                                actionQueueContainerAnimation.to = actionQueueContainer.xMin;
                            } else {
                                actionQueueContainerAnimation.to = actionQueueContainer.xMax;
                            }
                            actionQueueContainerAnimation.start();
                        }
                    }

                    onLastItemRemoved: {
                        actionQueueContainerAnimation.stop();
                        console.log("onLastItemRemoved");
                        actionQueueContainer.hidden = true;
                        console.log("from:" + actionQueueContainer.x + ", to: " + actionQueueContainer.xHidden);
                        console.log(actionQueueContainerAnimation.running);
                        actionQueueContainerAnimation.from = actionQueueContainer.x;
                        actionQueueContainerAnimation.to = actionQueueContainer.xHidden;
                        actionQueueContainerAnimation.start();
                        console.log(actionQueueContainerAnimation.running);
                    }
                }

            }

        }

        // ***************************************
        //                SEARCH
        // ***************************************

        Rectangle {
            id: searchBox
            z: 50
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: bottomSeparator.top
            height: search.text != "" ? 32 : 0
            color: "#fff"
            border.width: 2
            border.color: "#111"
            //enabled: ui.state == "browse"

            TextInput {
                id: search
                anchors.fill: parent
                anchors.leftMargin: 4
                font.pixelSize: 24
                onTextChanged: {
                    if(ui.state == "applications") {
                        applications.updateModel()
                    } else {
                        packageList.updateModel()
                    }
                }
            }
        }

        // ***************************************
        //                STATUS
        // ***************************************

        Rectangle {
            id: bottomSeparator
            z: 50
            height: 4
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: statusContainer.top
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#fff" }
                GradientStop { position: 1.0; color: "#ddd" }
            }

        }

        Rectangle {
            id: statusContainer

            z: 50
            height: 48
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#ddd" }
                GradientStop { position: 0.8; color: "#ccc" }
                GradientStop { position: 1.0; color: "#aaa" }
            }

            ListView {
                id: status
                clip: true
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: deviceButton.left
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
                    text: "" + message
                }
            }

            Button {
                id: deviceButton
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                width: 288

                label: "Device: " + installDevice.value
                color: "#ddd"
                toggleButton: true

                Rectangle {
                    id: deviceSelection
                    property variant deviceOptions: ui.milky.getDeviceList()
                    anchors.bottom: parent.top
                    visible: height > 0
                    height: parent.pressed ? childrenRect.height : 0
                    width: parent.width
                    color: "gray"

                    Text {
                        id: noDevicesFound
                        text: "No devices found"
                        font.pixelSize: 14
                        anchors.horizontalCenter: parent.horizontalCenter
                        visible: deviceListRepeater.count == 0
                    }
                    Column {
                        width: childrenRect.width
                        height: childrenRect.height
                        Repeater {
                            function getDevices() {
                                var list = []
                                if(typeof(customDevices.value) == "string" && customDevices.value.length != 0) {
                                    list.push({mountPoint: customDevices.value});
                                } else {
                                    for(var i = 0; i < customDevices.value.length; ++i) {
                                        list.push({mountPoint: customDevices.value[i]});
                                    }
                                }

                                for(var i = 0; i < deviceSelection.deviceOptions.length; ++i) {
                                    if(!/\/mnt\/(utmp|pnd)\/.*/.test(deviceSelection.deviceOptions[i].mountPoint))
                                        list.push(deviceSelection.deviceOptions[i])
                                }
                                return list;
                            }

                            id: deviceListRepeater
                            model: getDevices()


                            delegate: Button {
                                property string mountPoint: modelData.mountPoint
                                height: 32
                                width: deviceSelection.width
                                color: "#ccc"
                                label: mountPoint
                                onClicked: {
                                    installDevice.value = mountPoint;
                                    ui.milky.applyConfiguration();
                                    deviceButton.pressed = false;
                                    ui.milky.crawlDevice();
                                    syncButton.updateEnabled();
                                }
                            }
                        }
                    }
                }
            }
        }


        function handleMessage(messageType, messageData) {
            var messages = {}

            messages[MilkyEvents.Installing] = "Installing PND (id=" + messageData + ")";
            messages[MilkyEvents.Removing] = "Removing PND (id=" + messageData + ")";
            messages[MilkyEvents.Upgrading] = "Upgrading PND (id=" + messageData + ")";
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
