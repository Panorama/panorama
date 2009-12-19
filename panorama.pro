# panorama.pro - Project file for the Panorama source code distribution
QT += declarative
TARGET = panorama
TEMPLATE = app
INCLUDEPATH += lib/pandora-libraries/include
SOURCES += main.cpp \
    mainwindow.cpp \
    configuration.cpp \
    panoramaui.cpp \
    appaccumulator.cpp \
    applicationmodel.cpp \
    application.cpp \
    iconfinder.cpp \
    desktopfile.cpp \
    applicationfiltermodel.cpp \
    applicationfiltermethods.cpp
HEADERS += mainwindow.h \
    configuration.h \
    panoramaui.h \
    application.h \
    appaccumulator.h \
    applicationmodel.h \
    iconfinder.h \
    desktopfile.h \
    applicationfiltermodel.h \
    applicationfiltermethods.h
OTHER_FILES += root.qml
RESOURCES += default.qrc
