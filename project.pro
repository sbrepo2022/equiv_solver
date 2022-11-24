#-------------------------------------------------
#
# Project created by QtCreator 2022-11-12T19:38:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project
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

SOURCES += \
    circuitsettingsdialog.cpp \
    field/fieldfactory.cpp \
    field/fieldmodel.cpp \
    field/wire/wiremodel.cpp \
    fieldstyledialog.cpp \
        main.cpp \
        mainwindow.cpp \
        field/fieldview.cpp \
    field/fieldcontroller.cpp \
    field/grid/gridmodel.cpp \
    field/fieldgraphicsitem.cpp \
    field/circuit/circuitelementmodel.cpp \
    field/circuit/circuitelementfactory.cpp \
    startdialog.cpp \
    field/edit_modes/fieldeditmodecontroller.cpp \
    field/edit_modes/fieldselectmodecontroller.cpp \
    field/edit_modes/fieldwiremodecontroller.cpp \
    field/edit_modes/fielddeletemodecontroller.cpp \
    field/edit_modes/fielddrawelementmodecontroller.cpp

HEADERS += \
    circuitsettingsdialog.h \
    field/fieldfactory.h \
    field/fieldmodel.h \
    field/wire/wiremodel.h \
    fieldstyledialog.h \
        mainwindow.h \
        field/fieldview.h \
    field/fieldcontroller.h \
    field/grid/gridmodel.h \
    field/fieldgraphicsitem.h \
    field/circuit/circuitelementmodel.h \
    field/circuit/circuitelementfactory.h \
    startdialog.h \
    field/edit_modes/fieldeditmodecontroller.h \
    field/edit_modes/fieldselectmodecontroller.h \
    field/edit_modes/fieldwiremodecontroller.h \
    field/edit_modes/fielddeletemodecontroller.h \
    field/edit_modes/fielddrawelementmodecontroller.h

FORMS += \
        circuitsettingsdialog.ui \
        fieldstyledialog.ui \
        mainwindow.ui \
    startdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    application.qrc
