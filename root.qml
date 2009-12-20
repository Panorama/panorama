//root.qml - The QML file that is responsible for containing PandoraUI instances
import Qt 4.6

Item {
    anchors.fill: parent
    x: 0
    y: 0
    Keys.onPressed: {
        event.accepted = true;
    }
}
