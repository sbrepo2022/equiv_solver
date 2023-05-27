QT = core xml

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

OUT_PWD = $$OUT_PWD/../../..
SUBPROJECT_DIR = solvers/analog_solvers/transient_analysis
include($$PWD/../../../build_dirs_settings.pri)

SOURCES += \
        element_math_models/capacitormathmodel.cpp \
        element_math_models/currencysourcemathmodel.cpp \
        element_math_models/inductormathmodel.cpp \
        element_math_models/resistormathmodel.cpp \
        element_math_models/voltagesourcemathmodel.cpp \
        elementmathmodel.cpp \
        elementsloader.cpp \
        main.cpp

INCLUDEPATH += \
        ../../../Eigen

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    element_math_models/capacitormathmodel.h \
    element_math_models/currencysourcemathmodel.h \
    element_math_models/inductormathmodel.h \
    element_math_models/resistormathmodel.h \
    element_math_models/voltagesourcemathmodel.h \
    elementmathmodel.h \
    elementsloader.h
