# panorama.pro - Project file for the Panorama source code distribution
QT += declarative
TARGET = panorama
TEMPLATE = app
INCLUDEPATH += lib/pandora-libraries/include
OTHER_FILES += root.qml

libpnd.target = lib/pandora-libraries/libpnd.so.1
libpnd.commands = cd lib/pandora-libraries;make;cd ../..
QMAKE_EXTRA_TARGETS += libpnd
PRE_TARGETDEPS += lib/pandora-libraries/libpnd.so.1
LIBS += -Llib/pandora-libraries -lpnd

SOURCES += src/main.cpp \
    src/mainwindow.cpp \
    src/configuration.cpp \
    src/panoramaui.cpp \
    src/appaccumulator.cpp \
    src/applicationmodel.cpp \
    src/application.cpp \
    src/iconfinder.cpp \
    src/desktopfile.cpp \
    src/applicationfiltermodel.cpp \
    src/applicationfiltermethods.cpp \
    src/textfile.cpp \
    src/pndscanner.cpp \
    src/pnd.cpp
HEADERS += src/mainwindow.h \
    src/configuration.h \
    src/panoramaui.h \
    src/application.h \
    src/appaccumulator.h \
    src/applicationmodel.h \
    src/iconfinder.h \
    src/desktopfile.h \
    src/applicationfiltermodel.h \
    src/applicationfiltermethods.h \
    src/constants.h \
    src/textfile.h \
    src/pndscanner.h \
    src/pnd.h
OTHER_FILES += qrc/root.qml
RESOURCES += default.qrc
