import Qt 4.7

Rectangle {
    id: packageDetails

    clip: true
    property QtObject milky
    property string pndId
    property QtObject pnd: pndId ? milky.getPackage(pndId) : null

    color: "white"

    signal install();
    signal remove();
    signal upgrade();
    signal preview();
    signal back();

    Loader {
        anchors.fill: parent
        sourceComponent: pnd ? detailsContent : null
    }

    Component {
        id: detailsContent

        Item {
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

                    text: pnd.description
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
                        text: "Size: " + pnd.sizeString
                    }
                    Text {
                        id: versionText
                        text: "Current version: " + [pnd.currentVersionMajor, pnd.currentVersionMinor, pnd.currentVersionRelease, pnd.currentVersionBuild].join(".");
                    }
                    Text {
                        id: installedVersionText
                        text: "Installed version: " + [pnd.installedVersionMajor, pnd.installedVersionMinor, pnd.installedVersionRelease, pnd.installedVersionBuild].join(".");
                        visible: pnd.installed
                    }
                    Text {
                        id: lastUpdatedText
                        text: "Last updated: " + pnd.lastUpdatedString
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
                        if(pnd.previewPics.length == 0) {
                            return ""
                        } else {
                            return pnd.previewPics[0]
                        }
                    }

                    fillMode: Image.PreserveAspectFit
                    source:  selectImage()

                    MouseArea {
                        enabled: image.source != ""
                        anchors.fill: parent
                        onClicked: packageDetails.preview()
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
                        id: installButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: !pnd.installed
                        color: pnd.installed ? "#ccc" : "#cec"
                        label: "Install"
                        controlHint: "B"
                        enabled: !pnd.installed
                        onClicked: packageDetails.install()
                    }

                    Button {
                        id: upgradeButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: pnd.installed
                        color: pnd.hasUpdate ? "#cce" :  "#ccc"
                        label: "Upgrade"
                        controlHint: "Y"
                        enabled: pnd.hasUpdate
                        onClicked: packageDetails.upgrade()
                    }

                    Button {
                        id: removeButton
                        height: 32
                        anchors.left: parent.left
                        anchors.right: parent.right
                        visible: pnd.installed
                        color: pnd.installed ? "#ecc" :  "#ccc"
                        label: "Remove"
                        controlHint: "A"
                        enabled: pnd.installed
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
                        onClicked: packageDetails.back()
                    }
                }
            }
        }
    }
}
