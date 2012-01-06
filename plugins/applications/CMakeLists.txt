PROJECT(APPLICATIONS)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

FIND_PACKAGE(GTK2 COMPONENTS gtk)

SET(applications_SOURCES
    src/applicationsplugin.cpp
    src/appaccumulator.cpp
    src/applicationmodel.cpp
    src/application.cpp
    src/iconfinder.cpp
    src/desktopfile.cpp
    src/pndscanner.cpp
    src/pnd.cpp
    src/applicationfiltermodel.cpp
    src/applicationfiltermethods.cpp
    src/applicationattached.cpp
    src/applications.cpp)

SET(applications_HEADERS
    src/applicationsplugin.h
    src/application.h
    src/appaccumulator.h
    src/applicationmodel.h
    src/iconfinder.h
    src/desktopfile.h
    src/pndscanner.h
    src/pnd.h
    src/applicationfiltermodel.h
    src/applicationfiltermethods.h
    src/applicationattached.h
    src/applications.h)

QT4_WRAP_CPP(applications_HEADERS_MOC ${applications_HEADERS})

INCLUDE_DIRECTORIES(${PND_BINARY_DIR}/include/)

IF (GTK2_FOUND)
    INCLUDE_DIRECTORIES(${GTK2_INCLUDE_DIRS})
    ADD_DEFINITIONS(-DHAS_GTK)
ENDIF(GTK2_FOUND)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS} -DQT_PLUGIN -DQT_NO_DEBUG -DQT_SHARED)
ADD_LIBRARY(applications MODULE ${applications_SOURCES} ${applications_HEADERS_MOC})
TARGET_LINK_LIBRARIES(applications pnd)

IF (GTK2_FOUND)
    TARGET_LINK_LIBRARIES(applications ${GTK2_LIBRARIES})
ENDIF (GTK2_FOUND)

INSTALL(TARGETS applications DESTINATION ${PLUGINDIR}/Panorama/Applications)

