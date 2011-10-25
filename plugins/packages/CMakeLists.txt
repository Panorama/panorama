PROJECT(PACKAGES)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

SET(packages_SOURCES
    src/packagesplugin.cpp
    src/milkymodel.cpp
    src/milkylistener.cpp
    src/milkypackage.cpp
    src/packagefiltermodel.cpp
    src/packagefiltermethods.cpp
    src/milkydevice.cpp)

SET(packages_HEADERS
    src/packagesplugin.h
    src/milkymodel.h
    src/milkylistener.h
    src/milkypackage.h
    src/packagefiltermodel.h
    src/packagefiltermethods.h
    src/milkydevice.h)

QT4_WRAP_CPP(packages_HEADERS_MOC ${packages_HEADERS})

INCLUDE_DIRECTORIES(${PND_BINARY_DIR}/include/)
INCLUDE_DIRECTORIES(${JANSSON_BINARY_DIR}/include/)
INCLUDE_DIRECTORIES(${MILKY_BINARY_DIR}/include/)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_PLUGIN -DQT_NO_DEBUG -DQT_SHARED)
ADD_LIBRARY(packages MODULE ${packages_SOURCES} ${packages_HEADERS_MOC})
TARGET_LINK_LIBRARIES(packages milky pnd)
INSTALL(TARGETS packages DESTINATION ${PLUGINDIR}/Panorama/Milky)

