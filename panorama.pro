#pandora-libraries.pro - The qmake master project for pandora-libraries
TEMPLATE = subdirs
SUBDIRS = panorama \
    pandora-libraries

pandora-libraries.subdir = pandora-libraries

panorama.subdir = panorama
panorama.depends = pandora-libraries
