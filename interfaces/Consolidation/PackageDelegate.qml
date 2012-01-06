import Qt 4.7

Rectangle {
    id: packageDelegate

    property bool isInstalled: installed
    property bool hasUpgrade: hasUpdate

    signal showDetails();

    height: 32

    z: 10

    anchors.left: parent.left
    anchors.right: parent.right

    gradient: Gradient {
        GradientStop { position: 0; color: Qt.lighter(hasUpgrade ? "#eef" : "#eee", index % 2 ? 1.1 : 0.9) }
        GradientStop { position: 0.2; color: Qt.lighter(hasUpgrade ? "#ccd" : "#ddd", index % 2 ? 1.1 : 0.9) }
        GradientStop { position: 0.8; color: Qt.lighter(hasUpgrade ? "#bbc" : "#ccc", index % 2 ? 1.1 : 0.9) }
        GradientStop { position: 1; color: Qt.lighter(hasUpgrade ? "#99a" : "#aaa", index % 2 ? 1.1 : 0.9) }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            showDetails();
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
        font.pixelSize: 14
        color: "#111"
    }

}
