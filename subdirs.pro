TEMPLATE = subdirs

SUBDIRS = \
    gui \
    tests

tests.depends = gui
