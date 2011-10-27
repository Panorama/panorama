import Qt 4.7

Item {
    id: packageItem
    property bool detailsVisible: false
    property bool isInstalled: installed
    property bool hasUpgrade: hasUpdate

    signal install();
    signal remove();
    signal upgrade();
    signal preview();
    signal showDetails();

    anchors.left: parent.left
    anchors.right: parent.right
    height: detailsVisible ? 196 : 32
    Behavior on height {
        SequentialAnimation {
            NumberAnimation { duration: 300; easing.type: Easing.OutCubic }
            ScriptAction { script: packageItem.showDetails() }
        }
    }


    Rectangle {
        id: packageTitle
        height: 32
        z: 10
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        gradient: Gradient {
            GradientStop { position: 0; color: hasUpdate ? "#eef" : "#eee" }
            GradientStop { position: 0.2; color: hasUpdate ? "#ccd" : "#ddd" }
            GradientStop { position: 0.8; color: hasUpdate ? "#bbc" : "#ccc" }
            GradientStop { position: 1; color: hasUpdate ? "#99a" : "#aaa" }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                packageItem.detailsVisible = !packageItem.detailsVisible;
                if(packageItem.detailsVisible) {
                    showDetails();
                }
            }

        }
        Image {
            id: iconImage
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            width: 24
            height: 24
            smooth: true
            sourceSize {
                width: 24
                height: 24
            }

            // Set source only once, when the list is moving slow enough. Binding loop evasion manouver.
            function setSource() {
                if(Math.abs(packageItem.ListView.view.verticalVelocity) < 500) {
                    source = icon;
                }
                return true;
            }
            property bool foo: setSource()
            source: ""
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
            font.pixelSize: 14
            color: "#111"
        }

    }

    Rectangle {
        id: packageDetails
        visible: packageItem.height > packageTitle.height
        anchors.top: packageTitle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        color: "white"

        Flickable {
            id: descriptionContainer
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: previewContainer.left
            anchors.bottom: sizeAndVersion.top

            contentWidth: descriptionText.paintedWidth
            contentHeight: descriptionText.paintedHeight
            flickableDirection: Flickable.VerticalFlick
            boundsBehavior: Flickable.StopAtBounds
            clip: true

            Text {
                id: descriptionText
                anchors.top: parent.top
                width: descriptionContainer.width

                text: description
                color: "#222"
                font.pixelSize: 16
                wrapMode: Text.WordWrap
            }
        }
        Rectangle {
            id: sizeAndVersion
            anchors.left: parent.left
            anchors.right: previewContainer.left
            anchors.bottom: installButton.top
            color: "#eee"
            height: 16
            visible: packageItem.height > packageTitle.height + height
            Row {
                anchors.fill: parent
                spacing: 16
                Text {
                    id: sizeText
                    text: "Size: " + sizeString
                }
                Text {
                    id: versionText
                    text: "Current version: " + [currentVersionMajor, currentVersionMinor, currentVersionRelease, currentVersionBuild].join(".");
                }
                Text {
                    id: installedVersionText
                    text: "Installed version: " + [installedVersionMajor, installedVersionMinor, installedVersionRelease, installedVersionBuild].join(".");
                    visible: installed
                }
                Text {
                    id: lastUpdatedText
                    text: "Last updated: " + lastUpdatedString
                }
            }
        }
        Rectangle {
            id: previewContainer
            color: "#444"
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.bottom: installButton.top
            width: previewPics.length ? 192 : 0

            Text {
                anchors.centerIn: parent
                opacity: image.status != Image.Ready && image.source != "" ? 1.0 : 0.0
                text: parseInt(image.progress * 100) + "%"
                font.pixelSize: 24
                color: "#ddd"
            }

            Image {
                id: image
                function selectImage() {
                    if(!packageItem.detailsVisible) {
                        return ""
                    } else if(previewPics.length == 0) {
                        return ""
                    } else {
                        return previewPics[0]
                    }
                }

                height: previewContainer.height
                width: previewContainer.width
                fillMode: Image.PreserveAspectFit
                source:  selectImage()

                MouseArea {
                    anchors.fill: parent
                    onClicked: packageItem.preview()
                }
            }


        }

        Button {
            id: installButton
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: 32
            width: visible ? parent.width : 0
            visible: !installed
            color: installed ? "#ccc" : "#cec"
            label: "Install"
            controlHint: "X"
            enabled: !installed
            onClicked: packageItem.install()
        }

        Button {
            id: upgradeButton
            anchors.bottom: parent.bottom
            anchors.left: installButton.right
            anchors.right: removeButton.left
            height: 32
            width: visible ? parent.width / 2 : 0
            visible: installed
            color: hasUpdate ? "#cce" :  "#ccc"
            label: "Upgrade"
            controlHint: "Y"
            enabled: hasUpdate
            onClicked: packageItem.upgrade()
        }

        Button {
            id: removeButton
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            height: 32
            width: visible ? parent.width / 2 : 0
            visible: installed

            color: installed ? "#ecc" :  "#ccc"
            label: "Remove"
            controlHint: "A"
            enabled: installed
            onClicked: packageItem.remove()
        }
    }
}
