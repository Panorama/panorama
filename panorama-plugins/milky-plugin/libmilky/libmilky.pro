TEMPLATE = lib
CONFIG += staticlib
TARGET = milky
SOURCES = \
    src/lib/alpm_list.c \
    src/lib/milky.c \
    src/lib/conf.c \
    src/lib/file.c \
    src/lib/parseconfig.c \
    src/lib/dev.c \
    src/lib/json.c \
    src/lib/curl.c \
    src/lib/pnd.c \
    src/lib/sync.c \
    src/lib/md5.c \
    src/lib/download.c \
    src/lib/install.c \
    src/lib/crawl.c \
    src/lib/remove.c \
    src/lib/upgrade.c \
    src/lib/logfile.c


HEADERS = \
    src/lib/alpm_list.h \
    src/lib/conf.h \
    src/lib/crawl.h \
    src/lib/curl.h \
    src/lib/dev.h \
    src/lib/download.h \
    src/lib/event.h \
    src/lib/file.h \
    src/lib/install.h \
    src/lib/json.h \
    src/lib/md5.h \
    src/lib/milky.h \
    src/lib/parseconfig.h \
    src/lib/pnd_container.h \
    src/lib/pnd_discovery.h \
    src/lib/pnd.h \
    src/lib/remove.h \
    src/lib/sync.h \
    src/lib/upgrade.h \
    src/lib/logfile.h \
    src/lib/version.h
INCLUDEPATH += ../../../pandora-libraries/include
INCLUDEPATH += src/lib
INCLUDEPATH += ../libjansson/src/src
