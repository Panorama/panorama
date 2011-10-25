PROJECT(SETTINGS)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

SET(settings_SOURCES
    src/settingsplugin.cpp
    src/configuration.cpp
    src/setting.cpp
    src/settingshive.cpp
    src/settingssource.cpp)

SET(settings_HEADERS
    src/settingsplugin.h
    src/configuration.h
    src/setting.h
    src/settingshive.h
    src/settingssource.h)

QT4_WRAP_CPP(settings_HEADERS_MOC ${settings_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_PLUGIN -DQT_NO_DEBUG -DQT_SHARED)
ADD_LIBRARY(settings MODULE ${settings_SOURCES} ${settings_HEADERS_MOC})
INSTALL(TARGETS settings DESTINATION ${PLUGINDIR}/Panorama/Settings)

