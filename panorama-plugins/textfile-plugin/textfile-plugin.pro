TEMPLATE = lib
TARGET  = textfile
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../panorama/target/plugins

INCLUDEPATH += ../../panorama/include

SOURCES += \
    src/textfileplugin.cpp \
    src/textfile.cpp

HEADERS += \
    src/textfileplugin.h \
    src/textfile.h
