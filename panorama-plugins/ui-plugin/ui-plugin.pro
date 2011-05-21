TEMPLATE = lib
TARGET  = ui
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../panorama/target/plugins/Panorama/UI

INCLUDEPATH += ../../panorama/include

SOURCES += \
    src/uiplugin.cpp \
    src/panoramaui.cpp

HEADERS += \
    src/uiplugin.h \
    src/panoramaui.h
