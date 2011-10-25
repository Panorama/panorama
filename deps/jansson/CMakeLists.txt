PROJECT(JANSSON)

SET(jansson_SOURCES
    src/src/dump.c
    src/src/error.c
    src/src/hashtable.c
    src/src/load.c
    src/src/memory.c
    src/src/pack_unpack.c
    src/src/strbuffer.c
    src/src/utf.c
    src/src/value.c)

SET(jansson_HEADERS
    src/src/hashtable.h
    src/src/jansson.h
    src/src/jansson_private.h
    src/src/strbuffer.h
    src/src/utf.h)

SET(jansson_INCLUDES
    src/src/jansson.h
    src/src/jansson_config.h)

INCLUDE_DIRECTORIES(src/src/)

FILE(COPY ${jansson_INCLUDES} DESTINATION include)
ADD_DEFINITIONS(-fPIC)
ADD_LIBRARY(jansson ${jansson_SOURCES} ${jansson_HEADERS})

