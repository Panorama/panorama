PROJECT(PND)

SET(pnd_SOURCES
    src/lib/pnd_apps.c
    src/lib/pnd_conf.c
    src/lib/pnd_container.c
    src/lib/pnd_dbusnotify.c
    src/lib/pnd_desktop.c
    src/lib/pnd_device.c
    src/lib/pnd_discovery.c
    src/lib/pnd_io_evdev.c
    src/lib/pnd_io_gpio.c
    src/lib/pnd_io_ioctl.c
    src/lib/pnd_locate.c
    src/lib/pnd_logger.c
    src/lib/pnd_notify.c
    src/lib/pnd_pndfiles.c
    src/lib/pnd_pxml.c
    src/lib/pnd_tinyxml.cpp
    src/lib/pnd_utility.c
    src/lib/tinyxml/tinystr.cpp
    src/lib/tinyxml/tinyxml.cpp
    src/lib/tinyxml/tinyxmlerror.cpp
    src/lib/tinyxml/tinyxmlparser.cpp)

SET(pnd_HEADERS
    src/include/pnd_apps.h
    src/include/pnd_conf.h
    src/include/pnd_container.h
    src/include/pnd_dbusnotify.h
    src/include/pnd_desktop.h
    src/include/pnd_device.h
    src/include/pnd_discovery.h
    src/include/pnd_io_evdev.h
    src/include/pnd_io_gpio.h
    src/include/pnd_io_ioctl.h
    src/include/pnd_locate.h
    src/include/pnd_logger.h
    src/include/pnd_notify.h
    src/include/pnd_pndfiles.h
    src/include/pnd_pxml.h
    src/include/pnd_pxml_names.h
    src/include/pnd_tinyxml.h
    src/include/pnd_utility.h
    src/include/pnd_version.h
    src/lib/pnd_pathiter.h
    src/lib/pnd_keytype.h
    src/lib/tinyxml/tinystr.h
    src/lib/tinyxml/tinyxml.h)

SET(pnd_INCLUDES
    src/include/pnd_apps.h
    src/include/pnd_conf.h
    src/include/pnd_container.h
    src/include/pnd_dbusnotify.h
    src/include/pnd_desktop.h
    src/include/pnd_device.h
    src/include/pnd_discovery.h
    src/include/pnd_io_evdev.h
    src/include/pnd_io_gpio.h
    src/include/pnd_io_ioctl.h
    src/include/pnd_locate.h
    src/include/pnd_logger.h
    src/include/pnd_notify.h
    src/include/pnd_pndfiles.h
    src/include/pnd_pxml.h
    src/include/pnd_pxml_names.h
    src/include/pnd_tinyxml.h
    src/include/pnd_utility.h
    src/include/pnd_version.h)

INCLUDE_DIRECTORIES(src/include/)

FILE(COPY ${pnd_INCLUDES} DESTINATION include)
ADD_DEFINITIONS(-fPIC)
ADD_LIBRARY(pnd ${pnd_SOURCES} ${pnd_HEADERS})

