TEMPLATE = lib
TARGET  = settings
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../target/plugins/Panorama/Settings

pandora {
    DEFINES += PANDORA
}

CONFIG(release, debug|release) {
    DEFINES += RELEASE
}

INCLUDEPATH += ../../panorama/include

SOURCES += \
    src/settingsplugin.cpp \
    src/configuration.cpp \
    src/setting.cpp \
    src/settingshive.cpp \
    src/settingssource.cpp

HEADERS += \
    src/settingsplugin.h \
    src/configuration.h \
    src/setting.h \
    src/settingshive.h \
    src/settingssource.h
