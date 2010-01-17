# panorama.pro - Project file for the Panorama source code distribution
QT += declarative
TARGET = panorama
DESTDIR = target
TEMPLATE = app
INCLUDEPATH += ../pandora-libraries/pnd/include
OTHER_FILES += root.qml
LIBS += -L../pandora-libraries/pnd \
    -lpnd
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
    src/pnd.cpp \
    src/setting.cpp \
    src/systeminformation.cpp \
    src/settingshive.cpp
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
    src/pnd.h \
    src/setting.h \
    src/systeminformation.h \
    src/settingshive.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
