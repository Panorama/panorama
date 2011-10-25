PROJECT(MILKY)

FIND_PACKAGE(CURL REQUIRED)
FIND_PACKAGE(OpenSSL REQUIRED)

SET(milky_SOURCES
    src/lib/alpm_list.c
    src/lib/milky.c
    src/lib/conf.c
    src/lib/file.c
    src/lib/parseconfig.c
    src/lib/dev.c
    src/lib/json.c
    src/lib/curl.c
    src/lib/pnd.c
    src/lib/sync.c
    src/lib/md5.c
    src/lib/download.c
    src/lib/install.c
    src/lib/crawl.c
    src/lib/remove.c
    src/lib/upgrade.c)

SET(milky_HEADERS
    src/lib/alpm_list.h
    src/lib/conf.h
    src/lib/crawl.h
    src/lib/curl.h
    src/lib/dev.h
    src/lib/download.h
    src/lib/event.h
    src/lib/file.h
    src/lib/install.h
    src/lib/json.h
    src/lib/md5.h
    src/lib/milky.h
    src/lib/parseconfig.h
    src/lib/pnd_container.h
    src/lib/pnd_discovery.h
    src/lib/pnd.h
    src/lib/remove.h
    src/lib/sync.h
    src/lib/upgrade.h)

SET(milky_INCLUDES src/include/milky/milky.h src/lib/alpm_list.h)

INCLUDE_DIRECTORIES(src/lib/)
INCLUDE_DIRECTORIES(${JANSSON_BINARY_DIR}/include/)
INCLUDE_DIRECTORIES(${PND_BINARY_DIR/include/})

FILE(COPY ${milky_INCLUDES} DESTINATION include/milky/)
ADD_DEFINITIONS(-fPIC)
ADD_LIBRARY(milky ${milky_SOURCES} ${milky_HEADERS})
TARGET_LINK_LIBRARIES(milky m curl ssl jansson stdc++ pnd)

