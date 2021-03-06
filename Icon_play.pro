#-------------------------------------------------
#
# Project created by QtCreator 2017-08-06T23:10:18
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Icon_play
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    singleapplication.cpp \
    iceplayer.cpp \
    ice_button.cpp \
    icelabel.cpp \
    ice_vol_button.cpp \
    ice_miniwindow.cpp \
    networker.cpp \
    nofocusdelegate.cpp \
    ice_lrc.cpp \
    ice_lrc_label.cpp

HEADERS  += \
    singleapplication.h \
    iceplayer.h \
    ice_button.h \
    icelabel.h \
    ice_vol_button.h \
    ice_miniwindow.h \
    networker.h \
    nofocusdelegate.h \
    ice_lrc.h \
    ice_lrc_label.h

RESOURCES += \
    resource.qrc

DISTFILES += \
    README.md
