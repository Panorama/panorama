TEMPLATE = lib
CONFIG += staticlib
TARGET = jansson
SOURCES = \
    src/src/dump.c \
    src/src/error.c \
    src/src/hashtable.c \
    src/src/load.c \
    src/src/memory.c \
    src/src/pack_unpack.c \
    src/src/strbuffer.c \
    src/src/utf.c \
    src/src/value.c



HEADERS = \
    src/src/hashtable.h \
    src/src/jansson.h \
    src/src/jansson_private.h \
    src/src/strbuffer.h \
    src/src/utf.h


INCLUDEPATH += src/src

!exists(src/src/jansson_config.h) {
    system(cp jansson_config.h src/src)
}
