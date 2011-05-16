# panorama.pro - Project file for the Panorama source code distribution
QT += declarative

pandora {
    message(Building for Pandora)
    DEFINES += PANDORA
}

enable_opengl {
    message(OpenGL support enabled)
    DEFINES += ENABLE_OPENGL
    QT += opengl
} else {
    message(OpenGL support disabled)
}

poltergeist {
    message(Poltergeist enabled)
    DEFINES += POLTERGEIST
}

TARGET = panorama
DESTDIR = target
TEMPLATE = app
INCLUDEPATH += ../pandora-libraries/pnd/include
OTHER_FILES += root.qml
LIBS += -L../pandora-libraries/pnd \
    -lpnd
SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/configuration.cpp \
    src/panoramaui.cpp \
    src/appaccumulator.cpp \
    src/applicationmodel.cpp \
    src/application.cpp \
    src/iconfinder.cpp \
    src/desktopfile.cpp \
    src/applicationfiltermodel.cpp \
    src/applicationfiltermethods.cpp \
    src/textfile.cpp \
    src/pndscanner.cpp \
    src/pnd.cpp \
    src/setting.cpp \
    src/systeminformation.cpp \
    src/settingshive.cpp \
    src/settingssource.cpp \
    src/pandoraeventsource.cpp \
    src/pandora.cpp \
    src/pandoraattached.cpp \
    src/pandoraeventlistener.cpp \
    src/applicationattached.cpp \
    src/applications.cpp \
    src/pandorakeyevent.cpp
HEADERS += src/mainwindow.h \
    src/configuration.h \
    src/panoramaui.h \
    src/application.h \
    src/appaccumulator.h \
    src/applicationmodel.h \
    src/iconfinder.h \
    src/desktopfile.h \
    src/applicationfiltermodel.h \
    src/applicationfiltermethods.h \
    src/constants.h \
    src/textfile.h \
    src/pndscanner.h \
    src/pnd.h \
    src/setting.h \
    src/systeminformation.h \
    src/settingshive.h \
    src/settingssource.h \
    src/pandoraeventsource.h \
    src/pandora.h \
    src/pandoraattached.h \
    src/pandoraeventlistener.h \
    src/panoramainternal.h \
    src/applicationattached.h \
    src/applications.h \
    src/pandorakeyevent.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
