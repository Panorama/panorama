TEMPLATE = subdirs

SUBDIRS = \
    plugin \
    libmilky \
    libjansson

plugin.depends = libmilky
libmilky.depends = libjansson
