CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(PANORAMA)

# Package name
SET(PANORAMA_NAME "panorama")

# Package description
SET(PANORAMA_DESCRIPTION
    "A vivid graphical user environment with a solid plugin architecture.")

# Change the version numbers when making a panorama release (the current
# "development" version is always 0.0.0)
# TODO: Tag the development version differently somehow, so that you can have a
# devel and stable version installed in parallel.

# Increment when panorama reaches some major milestone
SET(PANORAMA_VERSION_MAJOR 0)

# Increment when panorama loses binary/source compatibility with a previous
# version (interfaces, plugins, ...). When a specific plugin loses
# compatibility with a previous version, set that plugin's version to
# "${PANORAMA_VERSION_MAJOR}.${PANORAMA_VERSION_MINOR}" and update interfaces
# accordingly.
# While Panorama still is in the 0.x version range, all plugins are considered
# unstable and set to version 1.0 for that reason.
SET(PANORAMA_VERSION_MINOR 0)

# Increment every time Panorama is released and none of the above applies. 
SET(PANORAMA_VERSION_PATCH 0)

# Forking Panorama? Congrats, you are the new vendor!
SET(PANORAMA_VENDOR "Panorama")

# Makes Panorama organize its files so that they are in the same base
# directory.
OPTION(PANDORA "Build for Pandora or another monolithic package system")

# Enables graphics acceleration for drawing primitives.
OPTION(OPENGL "Enable OpenGL rendering")

# This is for testing Pandora controls on the desktop, where it's impossible to
# emulate them somehow.
OPTION(POLTERGEIST "Test the event system with a poltergeist")

CONFIGURE_FILE(
    include/panoramaconfig.h.in
    include/panoramaconfig.h)

IF(PANDORA)
    MESSAGE("-- Compiling and packaging for the Pandora")
    INSTALL(DIRECTORY interfaces/ DESTINATION interfaces)
    SET(PLUGINDIR plugins)
ELSE(PANDORA)
    MESSAGE("-- Compiling and packaging for the Linux Desktop")
    INSTALL(DIRECTORY interfaces/ DESTINATION share/panorama/interfaces)
    SET(PLUGINDIR lib/panorama/plugins)
ENDIF(PANDORA)

IF(PANDORA)
    ADD_DEFINITIONS(-DPANDORA)
ENDIF(PANDORA)

IF(OPENGL)
    ADD_DEFINITIONS(-DENABLE_OPENGL)
    SET(QT_USE_QTOPENGL TRUE)
ENDIF(OPENGL)

IF(POLTERGEIST)
    ADD_DEFINITIONS(-DPOLTERGEIST)
ENDIF(POLTERGEIST)

INCLUDE_DIRECTORIES(${PANORAMA_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${PANORAMA_BINARY_DIR}/include/)

ADD_SUBDIRECTORY(deps)
ADD_SUBDIRECTORY(core)
ADD_SUBDIRECTORY(plugins)
ADD_SUBDIRECTORY(contrib)

SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${PANORAMA_SOURCE_DIR}/README.markdown)
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PANORAMA_DESCRIPTION})
SET(CPACK_PACKAGE_NAME ${PANORAMA_NAME})
SET(CPACK_PACKAGE_VENDOR ${PANORAMA_VENDOR})
SET(CPACK_PACKAGE_VERSION_MAJOR ${PANORAMA_VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${PANORAMA_VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${PANORAMA_VERSION_PATCH})
SET(CPACK_STRIP_FILES TRUE)
SET(CPACK_RESOURCE_FILE_LICENSE ${PANORAMA_SOURCE_DIR}/LICENSE)
SET(CPACK_RESOURCE_FILE_README ${PANORAMA_SOURCE_DIR}/README.markdown)
INCLUDE(CPack)

