QT       -= gui

TARGET = panorama-control
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += include

SOURCES += \
    src/control.cpp \
    src/concept.cpp

HEADERS += \
    include/control.h \
    include/concept.h \
    include/controlplugin.h
