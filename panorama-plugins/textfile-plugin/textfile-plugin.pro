TEMPLATE = lib
TARGET  = textfile
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../target/plugins/Panorama/TextFile

INCLUDEPATH += ../../panorama/include

SOURCES += \
    src/textfileplugin.cpp \
    src/textfile.cpp

HEADERS += \
    src/textfileplugin.h \
    src/textfile.h
