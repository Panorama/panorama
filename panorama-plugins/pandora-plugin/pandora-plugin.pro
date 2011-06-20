TEMPLATE = lib
TARGET  = pandora
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../target/plugins/Panorama/Pandora

INCLUDEPATH += ../../panorama/include
INCLUDEPATH += ../../pandora-libraries/include

LIBS += \
    -L../../pandora-libraries \
    -lpnd

SOURCES += \
    src/pandoraplugin.cpp \
    src/pandoraeventsource.cpp \
    src/pandora.cpp \
    src/pandoraattached.cpp \
    src/pandoraeventlistener.cpp \
    src/pandorakeyevent.cpp

HEADERS += \
    src/pandoraplugin.h \
    src/pandoraeventsource.h \
    src/pandora.h \
    src/pandoraattached.h \
    src/pandoraeventlistener.h \
    src/pandorakeyevent.h
