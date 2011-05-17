#panorama.pro - The qmake master project for panorama
TEMPLATE = subdirs
SUBDIRS = panorama \
    pandora-libraries \
    panorama-plugins

pandora-libraries.subdir = pandora-libraries

panorama.subdir = panorama
panorama.depends = panorama-plugins

panorama-plugins.subdir = panorama-plugins
panorama-plugins.depends = pandora-libraries
