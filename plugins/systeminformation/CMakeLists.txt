PROJECT(SYSTEMINFORMATION)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

SET(systeminformation_SOURCES
    src/systeminformationplugin.cpp
    src/systeminformation.cpp
    src/systeminformationattached.cpp)

SET(systeminformation_HEADERS
    src/systeminformationplugin.h
    src/systeminformation.h
    src/systeminformationattached.h)

QT4_WRAP_CPP(systeminformation_HEADERS_MOC ${systeminformation_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_PLUGIN -DQT_NO_DEBUG -DQT_SHARED)
ADD_LIBRARY(systeminformation MODULE ${systeminformation_SOURCES} ${systeminformation_HEADERS_MOC})
INSTALL(TARGETS systeminformation DESTINATION ${PLUGINDIR}/Panorama/SystemInformation)

