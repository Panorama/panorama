PROJECT(PANDORA)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

SET(pandora_SOURCES
    src/pandoraplugin.cpp
    src/pandoraeventsource.cpp
    src/pandora.cpp
    src/pandoraattached.cpp
    src/pandoraeventlistener.cpp
    src/pandorakeyevent.cpp)

SET(pandora_HEADERS
    src/pandoraplugin.h
    src/pandoraeventsource.h
    src/pandora.h
    src/pandoraattached.h
    src/pandoraeventlistener.h
    src/pandorakeyevent.h)

QT4_WRAP_CPP(pandora_HEADERS_MOC ${pandora_HEADERS})

INCLUDE_DIRECTORIES(${PND_BINARY_DIR}/include/)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_PLUGIN -DQT_NO_DEBUG -DQT_SHARED)
ADD_LIBRARY(pandora MODULE ${pandora_SOURCES} ${pandora_HEADERS_MOC})
TARGET_LINK_LIBRARIES(pandora pnd)
INSTALL(TARGETS pandora DESTINATION ${PLUGINDIR}/Panorama/Pandora)

