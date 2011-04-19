#panorama.pro - The qmake master project for panorama
TEMPLATE = subdirs
SUBDIRS = panorama \
    pandora-libraries

pandora-libraries.subdir = pandora-libraries

panorama.subdir = panorama
panorama.depends = pandora-libraries
