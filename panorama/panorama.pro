# panorama.pro - Project file for the Panorama source code distribution
QT += declarative opengl

pandora {
    message(Building for Pandora)
    QMAKE_LFLAGS = -L$$(PND_BASEDIR)/$$(PRJ)/lib -L$$(SDK_PATH)/$$(TARGET_SYS)/usr/lib -Wl,-O2,-rpath,$$(PND_BASEDIR)/$$(PRJ)/lib:$$(SDK_PATH)/$$(TARGET_SYS)/usr/lib
    QMAKE_INCDIR_QT = $$(PND_BASEDIR)/$$(PRJ)/include
    DEFINES += PANDORA
}

disable_opengl {
    message(OpenGL support disabled)
    DEFINES += DISABLE_OPENGL
    QT -= opengl
} else {
    message(OpenGL support enabled)
}


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
    src/settingshive.cpp \
    src/settingssource.cpp \
    src/pandoraeventsource.cpp \
    src/pandora.cpp
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
    src/settingshive.h \
    src/settingssource.h \
    src/pandoraeventsource.h \
    src/pandora.h
OTHER_FILES += qrc/root.qml
RESOURCES += qrc/default.qrc
