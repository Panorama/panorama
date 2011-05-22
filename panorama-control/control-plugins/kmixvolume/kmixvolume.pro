TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(kmixvolume)

QT = core dbus

LIBS += -L../../control -lpanorama-control
INCLUDEPATH += ../../control/include

DESTDIR = ../../../target/control-plugins

HEADERS += \
    src/kmixvolumeplugin.h \
    src/kmixvolumecontrol.h

SOURCES += \
    src/kmixvolumeplugin.cpp \
    src/kmixvolumecontrol.cpp
