TEMPLATE = lib
TARGET  = applications
QT += declarative
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = ../../target/plugins/Panorama/Applications

INCLUDEPATH += ../../panorama/include
INCLUDEPATH += ../../pandora-libraries/include

LIBS += \
    -L../../target/lib \
    -lpnd

SOURCES += \
    src/applicationsplugin.cpp \
    src/appaccumulator.cpp \
    src/applicationmodel.cpp \
    src/application.cpp \
    src/iconfinder.cpp \
    src/desktopfile.cpp \
    src/pndscanner.cpp \
    src/pnd.cpp \
    src/applicationfiltermodel.cpp \
    src/applicationfiltermethods.cpp \
    src/applicationattached.cpp \
    src/applications.cpp

HEADERS += \
    src/applicationsplugin.h \
    src/application.h \
    src/appaccumulator.h \
    src/applicationmodel.h \
    src/iconfinder.h \
    src/desktopfile.h \
    src/pndscanner.h \
    src/pnd.h \
    src/applicationfiltermodel.h \
    src/applicationfiltermethods.h \
    src/applicationattached.h \
    src/applications.h
