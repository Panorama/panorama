# panorama.pro - Project file for the Panorama source code distribution
QT += declarative

pandora {
    message(Building for Pandora)
    QMAKE_LFLAGS = -L$$(PND_BASEDIR)/$$(PRJ)/lib -L$$(SDK_PATH)/$$(TARGET_SYS)/usr/lib -Wl,-O2,-rpath,$$(PND_BASEDIR)/$$(PRJ)/lib:$$(SDK_PATH)/$$(TARGET_SYS)/usr/lib
    QMAKE_INCDIR_QT = $$(PND_BASEDIR)/$$(PRJ)/include
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
    src/settingssource.cpp
HEADERS += \
    include/panoramainternal.h \
    src/mainwindow.h \
    src/configuration.h \
    src/panoramaui.h \
    src/constants.h \
    src/setting.h \
    src/settingshive.h \
    src/settingssource.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
