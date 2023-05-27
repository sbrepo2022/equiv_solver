QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# build dir settings
OUT_PWD = $$OUT_PWD/..
SUBPROJECT_DIR = file_storage
include($$PWD/../build_dirs_settings.pri)

SOURCES += \
    $$PWD/filestorage.cpp

HEADERS += \
    $$PWD/filestorage.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
