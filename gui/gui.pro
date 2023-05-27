#-------------------------------------------------
#
# Project created by QtCreator 2022-11-12T19:38:09
#
#-------------------------------------------------

QT       += core gui svg charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = EquivSolver

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

# build dir settings
OUT_PWD = $$OUT_PWD/..
SUBPROJECT_DIR = gui
include($$PWD/../build_dirs_settings.pri)

DEPENDS += file_storage

INCLUDEPATH += $$PWD \
               $$PWD/../file_storage

SOURCES += \
    $$PWD/circuitsettingsdialog.cpp \
    $$PWD/custom_widgets/windowmanagebuttons.cpp \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/startdialog.cpp \
    $$PWD/custom_widgets/windowframemenubar.cpp \
    $$PWD/custom_widgets/framlessresizablewindow.cpp \
    $$PWD/field/fieldcontroller.cpp \
    $$PWD/fieldstyledialog.cpp \
    $$PWD/solverssettingsdialog.cpp \
    $$PWD/solverssettingstab.cpp \
    $$PWD/dock_widgets_controllers/selectablemodelview.cpp \
    $$PWD/field/fieldfactory.cpp \
    $$PWD/field/fieldmodel.cpp \
    $$PWD/field/wire/wiremodel.cpp \
    $$PWD/field/fieldview.cpp \
    $$PWD/field/grid/gridmodel.cpp \
    $$PWD/field/circuit/circuitelementmodel.cpp \
    $$PWD/field/circuit/circuitelementfactory.cpp \
    $$PWD/field/edit_modes/fieldeditmodecontroller.cpp \
    $$PWD/field/edit_modes/fieldselectmodecontroller.cpp \
    $$PWD/field/edit_modes/fieldwiremodecontroller.cpp \
    $$PWD/field/edit_modes/fielddeletemodecontroller.cpp \
    $$PWD/field/edit_modes/fielddrawelementmodecontroller.cpp \
    $$PWD/field/fieldscene.cpp \
    $$PWD/field/circuit/standart_circuit_elements/currencysourceelementmodel.cpp \
    $$PWD/field/circuit/standart_circuit_elements/voltagesourceelementmodel.cpp \
    $$PWD/field/circuit/standart_circuit_elements/resistorelementmodel.cpp \
    $$PWD/field/circuit/standart_circuit_elements/capacitorelementmodel.cpp \
    $$PWD/field/circuit/standart_circuit_elements/inductorelementmodel.cpp \
    $$PWD/field/circuit/standart_circuit_elements/groundelementmodel.cpp \
    $$PWD/field/fieldelementmodel.cpp \
    $$PWD/libs/formgenerator.cpp \
    $$PWD/model_components/basiccomponent.cpp \
    $$PWD/model_components/properties_components/capacitorpropertiescomponent.cpp \
    $$PWD/model_components/properties_components/currencysourcepropertiescomponent.cpp \
    $$PWD/model_components/properties_components/fieldelementpropertiescomponent.cpp \
    $$PWD/model_components/properties_components/inductorpropertiescomponent.cpp \
    $$PWD/model_components/properties_components/propertiescomponent.cpp \
    $$PWD/model_components/properties_components/resistorpropertiescomponent.cpp \
    $$PWD/model_components/properties_components/voltagesourcepropertiescomponent.cpp \
    $$PWD/model_components/selectablemodelcomponentskeeper.cpp \
    $$PWD/model_components/widgetcomponent.cpp \
    $$PWD/solver_connection/analog_solver_connection/analogsolvercontroller.cpp \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverconnector.cpp \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverpropertiescomponent.cpp \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverresult.cpp \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverrunner.cpp \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverserializer.cpp \
    $$PWD/solver_connection/solverconnector.cpp \
    $$PWD/solver_connection/solvercontroller.cpp \
    $$PWD/solver_connection/solverpropertiescomponent.cpp \
    $$PWD/solver_connection/solverprovider.cpp \
    $$PWD/solver_connection/solverresult.cpp \
    $$PWD/solver_connection/solverrunner.cpp \
    $$PWD/solver_connection/solverserializer.cpp

HEADERS += \
    $$PWD/circuitsettingsdialog.h \
    $$PWD/custom_widgets/windowmanagebuttons.h \
    $$PWD/mainwindow.h \
    $$PWD/startdialog.h \
    $$PWD/custom_widgets/windowframemenubar.h \
    $$PWD/custom_widgets/framlessresizablewindow.h \
    $$PWD/field/fieldcontroller.h \
    $$PWD/libs/qpoint_hash.h \
    $$PWD/fieldstyledialog.h \
    $$PWD/solverssettingsdialog.h \
    $$PWD/solverssettingstab.h \
    $$PWD/dock_widgets_controllers/selectablemodelview.h \
    $$PWD/field/fieldfactory.h \
    $$PWD/field/fieldmodel.h \
    $$PWD/field/wire/wiremodel.h \
    $$PWD/field/fieldview.h \
    $$PWD/field/grid/gridmodel.h \
    $$PWD/field/circuit/circuitelementmodel.h \
    $$PWD/field/circuit/circuitelementfactory.h \
    $$PWD/field/edit_modes/fieldeditmodecontroller.h \
    $$PWD/field/edit_modes/fieldselectmodecontroller.h \
    $$PWD/field/edit_modes/fieldwiremodecontroller.h \
    $$PWD/field/edit_modes/fielddeletemodecontroller.h \
    $$PWD/field/edit_modes/fielddrawelementmodecontroller.h \
    $$PWD/field/fieldscene.h \
    $$PWD/libs/qpoint_hash.h \
    $$PWD/field/circuit/standart_circuit_elements/currencysourceelementmodel.h \
    $$PWD/field/circuit/standart_circuit_elements/voltagesourceelementmodel.h \
    $$PWD/field/circuit/standart_circuit_elements/resistorelementmodel.h \
    $$PWD/field/circuit/standart_circuit_elements/capacitorelementmodel.h \
    $$PWD/field/circuit/standart_circuit_elements/inductorelementmodel.h \
    $$PWD/field/circuit/standart_circuit_elements/groundelementmodel.h \
    $$PWD/field/fieldelementmodel.h \
    $$PWD/libs/objectcounter.h \
    $$PWD/libs/formgenerator.h \
    $$PWD/model_components/basiccomponent.h \
    $$PWD/model_components/properties_components/capacitorpropertiescomponent.h \
    $$PWD/model_components/properties_components/currencysourcepropertiescomponent.h \
    $$PWD/model_components/properties_components/fieldelementpropertiescomponent.h \
    $$PWD/model_components/properties_components/inductorpropertiescomponent.h \
    $$PWD/model_components/properties_components/propertiescomponent.h \
    $$PWD/model_components/properties_components/resistorpropertiescomponent.h \
    $$PWD/model_components/properties_components/voltagesourcepropertiescomponent.h \
    $$PWD/model_components/selectablemodelcomponentskeeper.h \
    $$PWD/model_components/widgetcomponent.h \
    $$PWD/solver_connection/analog_solver_connection/analogsolvercontroller.h \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverconnector.h \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverpropertiescomponent.h \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverresult.h \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverrunner.h \
    $$PWD/solver_connection/analog_solver_connection/simple_dynamics_solver/transient_analysis/transientanalysissolverserializer.h \
    $$PWD/solver_connection/solverconnector.h \
    $$PWD/solver_connection/solvercontroller.h \
    $$PWD/solver_connection/solverpropertiescomponent.h \
    $$PWD/solver_connection/solverprovider.h \
    $$PWD/solver_connection/solverresult.h \
    $$PWD/solver_connection/solverrunner.h \
    $$PWD/solver_connection/solverserializer.h

FORMS += \
    $$PWD/circuitsettingsdialog.ui \
    $$PWD/custom_widgets/windowmanagebuttons.ui \
    $$PWD/fieldstyledialog.ui \
    $$PWD/mainwindow.ui \
    $$PWD/startdialog.ui \
    $$PWD/solverssettingsdialog.ui \
    $$PWD/solverssettingstab.ui

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

# Only for release mode
#CONFIG(release, debug|release) {
#    win32: system()
#}

