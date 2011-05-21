TEMPLATE = lib
TARGET  = systeminformation
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../panorama/target/plugins/Panorama/SystemInformation

INCLUDEPATH += ../../panorama/include

SOURCES += \
    src/systeminformationplugin.cpp \
    src/systeminformation.cpp \
    src/systeminformationattached.cpp

HEADERS += \
    src/systeminformationplugin.h \
    src/systeminformation.h \
    src/systeminformationattached.h
