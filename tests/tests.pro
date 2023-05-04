QT += core gui widgets svg testlib
CONFIG += qt warn_on depend_includepath testcase
CONFIG += c++14

TARGET = tests
TEMPLATE = app

SOURCES +=  tst_wiretests.cpp

include(../gui/gui.pri)
