QT += core gui widgets svg testlib
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++14

TARGET = tests
TEMPLATE = app

DEPENDS += gui

SOURCES += tst_wiretests.cpp

INCLUDEPATH = $$PWD

# build dir settings
OUT_PWD = $$OUT_PWD/..
SUBPROJECT_DIR = tests
include($$PWD/../build_dirs_settings.pri)
