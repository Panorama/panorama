TEMPLATE = subdirs

SUBDIRS = \
    control \
    control-plugins

control.subdir = control

control-plugins.subdir = control-plugins
control-plugins.depends = control
