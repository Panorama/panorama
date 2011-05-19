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
INCLUDEPATH += include
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/configuration.cpp \
    src/setting.cpp \
    src/settingshive.cpp \
    src/settingssource.cpp
HEADERS += \
    include/panoramainternal.h \
    include/constants.h \
    src/mainwindow.h \
    src/configuration.h \
    src/setting.h \
    src/settingshive.h \
    src/settingssource.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
