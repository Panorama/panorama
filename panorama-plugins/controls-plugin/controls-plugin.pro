TEMPLATE = lib
TARGET  = controls
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../target/plugins/Panorama/Controls

INCLUDEPATH += ../../panorama/include

SOURCES += \
    src/controlsplugin.cpp \
    src/controlwidget.cpp

HEADERS += \
    src/controlsplugin.h \
    src/controlwidget.h
