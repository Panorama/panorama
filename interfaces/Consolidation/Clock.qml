import Qt 4.7

Text {
    id: clock
    property alias color: clock.color
    property alias textSize: clock.font.pixelSize

    function zeroPad(integer, size) {
        var s = integer.toString()
        if(s.length < size) {
            for(var i = s.length; i < size; ++i) {
                s = "0" + s;
            }
        }
        return s;
    }

    function weekDayString(weekDayNumber) {
        var weekdays = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
        return weekdays[weekDayNumber];
    }

    text: weekDayString(time.weekday) + " " + time.year + "-" + zeroPad(time.month, 2) + "-" + zeroPad(time.day, 2) + " " + zeroPad(time.hour, 2) + ":" + zeroPad(time.minute, 2)

    Timer {
        id: time
        property int year
        property int month
        property int day
        property int weekday
        property int hour
        property int minute

        interval: 1000
        running: true
        repeat: true
        triggeredOnStart: true
        onTriggered: {
            var date = new Date;
            year = date.getFullYear();
            month = date.getMonth();
            day = date.getDate();
            weekday = date.getDay();
            hour = date.getHours();
            minute = date.getMinutes();
        }
    }
}
