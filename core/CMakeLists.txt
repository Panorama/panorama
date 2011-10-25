FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTDECLARATIVE TRUE)

SET(panorama_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/runtime.cpp)

SET(panorama_HEADERS
    src/mainwindow.h
    src/runtime.h)

SET(panorama_RESOURCES
    qrc/default.qrc)

QT4_WRAP_CPP(panorama_HEADERS_MOC ${panorama_HEADERS})
QT4_ADD_RESOURCES(panorama_RESOURCES_RCC ${panorama_RESOURCES})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_EXECUTABLE(panorama ${panorama_SOURCES} ${panorama_HEADERS_MOC} ${panorama_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(panorama ${QT_LIBRARIES})

IF(PANDORA)
    INSTALL(TARGETS panorama DESTINATION .)
ELSE(PANDORA)
    INSTALL(TARGETS panorama DESTINATION bin)
ENDIF(PANDORA)
