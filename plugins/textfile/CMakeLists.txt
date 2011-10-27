PROJECT(TEXTFILE)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

SET(textfile_SOURCES
    src/textfileplugin.cpp
    src/textfile.cpp)

SET(textfile_HEADERS
    src/textfileplugin.h
    src/textfile.h)

QT4_WRAP_CPP(textfile_HEADERS_MOC ${textfile_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_PLUGIN -DQT_NO_DEBUG -DQT_SHARED)
ADD_LIBRARY(textfile MODULE ${textfile_SOURCES} ${textfile_HEADERS_MOC})
INSTALL(TARGETS textfile DESTINATION ${PLUGINDIR}/Panorama/TextFile)
