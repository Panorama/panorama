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
INCLUDEPATH += ../pandora-libraries/pnd/include include
OTHER_FILES += root.qml
LIBS += \
    -L../pandora-libraries/pnd \
    -lpnd
SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/configuration.cpp \
    src/panoramaui.cpp \
    src/setting.cpp \
    src/settingshive.cpp \
    src/settingssource.cpp \
    src/pandoraeventsource.cpp \
    src/pandora.cpp \
    src/pandoraattached.cpp \
    src/pandoraeventlistener.cpp \
    src/pandorakeyevent.cpp
HEADERS += \
    include/panoramainternal.h \
    src/mainwindow.h \
    src/configuration.h \
    src/panoramaui.h \
    src/constants.h \
    src/setting.h \
    src/settingshive.h \
    src/settingssource.h \
    src/pandoraeventsource.h \
    src/pandora.h \
    src/pandoraattached.h \
    src/pandoraeventlistener.h \
    src/pandorakeyevent.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
