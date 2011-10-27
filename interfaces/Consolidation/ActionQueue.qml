import Qt 4.7
import Panorama.Milky 1.0

ListView {
    id: actionQueue
    property real progress: 0.0
    property bool empty: model.count == 0
    property bool downloading: false
    property QtObject milky
    model: ListModel {}

    signal itemAdded()
    signal lastItemRemoved()

    function setProgress(progress) {
        if(!empty && downloading) {
            model.setProperty(0, "progress", progress);
        }
    }

    function cancelItem(index) {
        var jobId = model.get(index).jobId;
        milky.cancelJob(jobId);
        removeItem(index);
    }

    function removeItem(index) {
        model.remove(index);
        if(empty) {
            console.log("lastItemRemoved");
            lastItemRemoved();
        }
        if(index == 0 && downloading) {
            progress = 0.0;
            downloading = false;
        }
    }

    Component.onCompleted: {
        milky.events.downloadStarted.connect(function() {
            downloading = true;
        });
        milky.installQueued.connect(function(pnd, jobId) {
            model.append({title: pnd.title, progress: 0, jobId: jobId});
            itemAdded();
        });
        milky.events.downloadFinished.connect(function() {
            downloading = false;
            if(!empty) {
                var jobId = model.get(0).jobId;
                removeItem(0);
            }
        });
    }

    delegate: width > 128 ? actionDelegate : smallActionDelegate

    Component {
        id: actionDelegate

        Rectangle {
            id: actionItem
            height: 52
            anchors.left: parent.left
            anchors.right: parent.right
            color: "#333"

            Text {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.margins: 2

                id: label
                font.pixelSize: 18
                width: parent.width/3
                text: title
                color:"#eee"
                height: 20
            }

            Row {
                id: progressRow
                anchors.top: label.bottom
                anchors.left: parent.left
                anchors.right: percentageLabel.left
                anchors.margins: 4
                height: 24
                spacing: 4
                Repeater {
                    model: 10
                    delegate: Rectangle {
                        function calcValue(progress) {
                            if(progress >= 10 * (index+1))
                                return 1.0
                            else if(progress < 10 * index)
                                return 0.0
                            else
                                return (progress % 10) / 10.0
                        }

                        property real value: calcValue(progress)

                        height: progressRow.height
                        width: progressRow.width/10 - 4
                        radius: 6
                        smooth: true
                        gradient: Gradient {
                            GradientStop { position: 0; color: Qt.rgba(0.5+(1.0-value)*0.5, 0.5+value*0.5, 0.5, 1.0) }
                            GradientStop { position: 1; color: Qt.rgba(0.5+(1.0-value)*0.8*0.5, 0.5+value*0.8*0.5, 0.5, 1.0) }
                        }
                    }
                }
            }
            Text {
                id: percentageLabel
                anchors.verticalCenter: progressRow.verticalCenter
                anchors.right: cancelButton.left
                anchors.rightMargin: 4
                text: progress + "%"
                font.pixelSize: 18
                color:"#eee"
            }
            Button {
                id: cancelButton

                anchors.verticalCenter: progressRow.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 4
                width: progressRow.height
                height: progressRow.height
                radius: 8
                color: "#faa"
                textColor: "#fff"
                label: "x"
                onClicked: actionQueue.cancelItem(index)
            }
        }
    }

    Component {
        id: smallActionDelegate
        Button {
            id: cancelButton

            width: actionQueue.width
            height: 64
            color: Qt.rgba(0.5+(100 - progress)/200.0, 0.5+progress/200.0, 0.5)
            textColor: "#fff"
            label: progress + "%"
            onClicked: actionQueue.cancelItem(index)
        }
    }

    Timer {
        running: actionQueue.downloading
        interval: 100
        repeat: true
        onTriggered: {
            if(actionQueue.milky.bytesToDownload && actionQueue.downloading) {
                var progress = parseInt(100.0 * actionQueue.milky.bytesDownloaded / actionQueue.milky.bytesToDownload);
                actionQueue.setProgress(progress);
            }
        }
    }
}
