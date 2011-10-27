import Qt 4.7

Rectangle {
    id: packageDetails

    clip: true
    property QtObject milky
    property string pndId: ""
    property QtObject pnd: milky.getPackage(pndId)
    property QtObject application: null
    property variant info: gatherInfo()
    state: "details"
    function gatherInfo() {
        var info = {}
        if(pnd !== null) {
            info.isPnd = true;
            info.size = pnd.sizeString;
            info.description = pnd.description ? pnd.description : "(no description)";
            info.currentVersion = [pnd.currentVersionMajor, pnd.currentVersionMinor, pnd.currentVersionRelease, pnd.currentVersionBuild].join(".");
            info.installedVersion = [pnd.installedVersionMajor, pnd.installedVersionMinor, pnd.installedVersionRelease, pnd.installedVersionBuild].join(".");
            info.lastUpdated = pnd.lastUpdatedString;
            info.previewPics = pnd.previewPics;
            info.installed = pnd.installed;
            info.hasUpdate = pnd.hasUpdate;
        } else if(application !== null) {
            info.isPnd = false;
            info.size = "-";
            info.description = application.description ? application.description : "(no description)";
            info.currentVersion = "-";
            info.installedVersion = application.version;
            info.lastUpdated = "-";
            info.previewPics = [];
            info.installed = true;
            info.hasUpdate = false;
        } else {
            console.log("*** PND: " + pnd + ", APPLICATION: " + application)
            info = null;
        }

        return info;
    }

    color: "white"

    signal install();
    signal remove();
    signal upgrade();
    signal back();
    signal deactivate();
    signal execute();

    onDeactivate: {
        pndId = "";
        application = null;
        state = "details";
    }

    onBack: {
        if(state == "previews") {
            state = "details";
        } else {
            deactivate();
        }
    }

    signal nextPreview();
    signal previousPreview();

    Loader {
        function pickComponent() {
            if(packageDetails.info !== null && packageDetails.state == "details")
                return detailsContent;
            else if(packageDetails.info !== null && packageDetails.state == "previews")
                return previewComponent;
            else
                return null;
        }

        anchors.fill: parent
        sourceComponent: pickComponent()
    }

    Component {
        id: detailsContent

        Item {
            Component.onCompleted: console.log(pndId)
            MouseArea { anchors.fill: parent; onPressed: mouse.accepted = true; }

            Flickable {
                id: descriptionContainer
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: sidebar.left
                anchors.bottom: parent.bottom
                anchors.topMargin: 8
                anchors.leftMargin: 8
                contentWidth: descriptionText.paintedWidth
                contentHeight: descriptionText.paintedHeight
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds

                Text {
                    id: descriptionText
                    anchors.top: parent.top
                    width: descriptionContainer.width

                    text: info.description
                    color: "#222"
                    font.pixelSize: 16
                    wrapMode: Text.WordWrap
                }
            }
            Rectangle {
                id: sizeAndVersion
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                color: "#eee"
                height: 16
                z: 1
                Row {
                    anchors.fill: parent
                    spacing: 16
                    Text {
                        id: sizeText
                        text: "Size: " + info.size
                    }
                    Text {
                        id: versionText
                        text: "Current version: " + info.currentVersion;
                    }
                    Text {
                        id: installedVersionText
                        text: "Installed version: " + info.installedVersion;
                        visible: info.installed
                    }
                    Text {
                        id: lastUpdatedText
                        text: "Last updated: " + info.lastUpdated
                    }
                }
            }
            Rectangle {
                id: sidebar
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: sizeAndVersion.top
                width: 192
                color: "#ddd"

                Image {
                    id: image
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: width

                    function selectImage() {
                        if(info.previewPics.length == 0) {
                            return ""
                        } else {
                            return info.previewPics[0]
                        }
                    }

                    fillMode: Image.PreserveAspectFit
                    source:  selectImage()

                    MouseArea {
                        enabled: image.source != ""
                        anchors.fill: parent
                        onClicked: packageDetails.state = "previews"
                    }

                    Text {
                        anchors.centerIn: parent
                        opacity: image.source != "" ? (image.status != Image.Ready && image.source != "" ? 1.0 : 0.0) : 1.0
                        text: image.source != "" ? parseInt(image.progress * 100) + "%" : "No preview"
                        font.pixelSize: 24
                        color: "#777"
                    }
                }

                Column {
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Button {
                        id: runButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: info.installed
                        color: "#dfd"
                        label: "Run"
                        controlHint: "B"
                        enabled: info.installed
                        onClicked: packageDetails.execute()
                    }

                    Button {
                        id: installButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: !info.installed
                        color: info.installed ? "#ccc" : "#cec"
                        label: "Install"
                        controlHint: "B"
                        enabled: !info.installed
                        onClicked: packageDetails.install()
                    }

                    Button {
                        id: upgradeButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: info.isPnd && info.installed
                        color: info.hasUpdate ? "#cce" :  "#ccc"
                        label: "Upgrade"
                        controlHint: "Y"
                        enabled: info.hasUpdate
                        onClicked: packageDetails.upgrade()
                    }

                    Button {
                        id: removeButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: info.isPnd && info.installed
                        color: info.installed ? "#ecc" :  "#ccc"
                        label: "Remove"
                        controlHint: "A"
                        enabled: info.installed
                        onClicked: packageDetails.remove()
                    }
                    Button {
                        id: backButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right

                        color: "#aaa"
                        label: "Back"
                        controlHint: "X"
                        enabled: true
                        onClicked: packageDetails.deactivate()
                    }
                }
            }



        }
    }

    Component {
        id: previewComponent
        Rectangle {
            color: "#444"

            ListView {
                id: previewList
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height * 0.9

                Component.onCompleted: {
                    packageDetails.nextPreview.connect(function() {
                       incrementCurrentIndex();
                    });
                    packageDetails.previousPreview.connect(function() {
                       decrementCurrentIndex();
                    });
                }

                orientation: ListView.Horizontal
                snapMode: ListView.SnapToItem
                flickDeceleration: 2500

                preferredHighlightBegin: width/2 - currentItem.width/2
                preferredHighlightEnd: width/2 + currentItem.width/2
                highlightRangeMode: ListView.StrictlyEnforceRange

                cacheBuffer: width*4
                spacing: 16
                boundsBehavior: ListView.DragOverBounds

                model: packageDetails.info.previewPics

                delegate: Rectangle {
                    color: image.status == Image.Ready ? "#00000000" : "#eee"
                    height: previewList.height
                    width: image.status == Image.Ready ? image.width : height

                    Text {
                        anchors.centerIn: parent
                        visible: image.status != Image.Ready
                        text: parseInt(image.progress * 100) + "%"
                        font.pixelSize: 24
                    }

                    Image {
                        id: image
                        source: modelData
                        height: parent.height
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
