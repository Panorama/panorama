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
    src/panoramaui.cpp \
    src/setting.cpp \
    src/settingshive.cpp \
    src/settingssource.cpp \
    src/runtime.cpp
HEADERS += \
    include/panoramainternal.h \
    src/mainwindow.h \
    src/configuration.h \
    src/panoramaui.h \
    src/constants.h \
    src/setting.h \
    src/settingshive.h \
    src/settingssource.h \
    src/runtime.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
