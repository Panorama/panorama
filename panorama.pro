#panorama.pro - The qmake master project for panorama
TEMPLATE = subdirs
SUBDIRS = panorama \
    pandora-libraries \
    panorama-plugins \
    panorama-control

pandora-libraries.subdir = pandora-libraries

panorama.subdir = panorama
panorama.depends = panorama-plugins

panorama-plugins.subdir = panorama-plugins
panorama-plugins.depends = pandora-libraries

unix {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    BINDIR = $$PREFIX/bin
    DATADIR = $$PREFIX/share
    LIBDIR = $$PREFIX/lib

    interfaces.files = target/interfaces/*
    interfaces.path = $$DATADIR/panorama/interfaces

    plugins.files = target/plugins/*
    plugins.path = $$LIBDIR/panorama/plugins/

    panorama.files = target/panorama
    panorama.path = $$BINDIR

    INSTALLS += interfaces plugins panorama
}
