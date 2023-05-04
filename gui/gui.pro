#-------------------------------------------------
#
# Project created by QtCreator 2022-11-12T19:38:09
#
#-------------------------------------------------

QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

include(gui.pri)

SOURCES += \
    $$PWD/circuitsettingsdialog.cpp \
    $$PWD/custom_widgets/windowmanagebuttons.cpp \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/startdialog.cpp \
    $$PWD/custom_widgets/windowframemenubar.cpp \
    $$PWD/custom_widgets/framlessresizablewindow.cpp \
    $$PWD/field/fieldcontroller.cpp \
    $$PWD/fieldstyledialog.cpp

HEADERS += \
    $$PWD/circuitsettingsdialog.h \
    $$PWD/custom_widgets/windowmanagebuttons.h \
    $$PWD/mainwindow.h \
    $$PWD/startdialog.h \
    $$PWD/custom_widgets/windowframemenubar.h \
    $$PWD/custom_widgets/framlessresizablewindow.h \
    $$PWD/field/fieldcontroller.h \
    $$PWD/libs/qpoint_hash.h \
    $$PWD/fieldstyledialog.h

FORMS += \
    $$PWD/circuitsettingsdialog.ui \
    $$PWD/custom_widgets/windowmanagebuttons.ui \
    $$PWD/fieldstyledialog.ui \
    $$PWD/mainwindow.ui \
    $$PWD/startdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    application.qrc \
    theme.qrc

RC_ICONS = resources/logo/icon.ico

DISTFILES += \
    custom_widgets/windowmanagebuttons.css

