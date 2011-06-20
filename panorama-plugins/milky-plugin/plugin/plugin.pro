TEMPLATE = lib
TARGET  = milky
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../../target/plugins/Panorama/Milky

INCLUDEPATH += ../../../panorama/include
INCLUDEPATH += ../libmilky/src/include
INCLUDEPATH += ../libmilky/src/lib
INCLUDEPATH += ../libjansson/src/src

SOURCES += \
    src/milkyplugin.cpp \
    src/milkymodel.cpp \
    src/milkylistener.cpp \
    src/milkypackage.cpp \
    src/packagefiltermodel.cpp \
    src/packagefiltermethods.cpp

HEADERS += \
    src/milkyplugin.h \
    src/milkymodel.h \
    src/milkylistener.h \
    src/milkypackage.h \
    src/packagefiltermodel.h \
    src/packagefiltermethods.h

LIBS += -L../libmilky -lmilky
LIBS += -L../libjansson -ljansson
LIBS += -L ../../../pandora-libraries -lpnd
LIBS += -lm -lcurl -lssl -lstdc++
