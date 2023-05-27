TEMPLATE = subdirs

SUBDIRS = \
    file_storage \
    gui \
    solvers
    \    #tests

gui.depends = file_storage solvers
#tests.depends = gui
