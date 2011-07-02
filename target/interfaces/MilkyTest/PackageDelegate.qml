import Qt 4.7

Item {
    id: packageItem
    property bool showDetails: false

    signal install();
    signal remove();
    signal upgrade();
    signal preview();

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
            anchors.right: previewContainer.left
            anchors.bottom: installButton.top

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
                    if(!packageItem.showDetails) {
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
                onClicked: packageItem.install()

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
                onClicked: packageItem.upgrade()
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
                onClicked: packageItem.remove()
            }
        }

    }
}
