#-------------------------------------------------
#
# Project created by QtCreator 2018-07-29T19:07:05
#
#-------------------------------------------------

QT += core gui
QT += gui
QMAKE_CXXFLAGS += -Wno-deprecated

TARGET = Communicate

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Blocks_and_Arrows
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


SOURCES += \
        main.cpp \
        dialog.cpp \
    block.cpp \
    myscene.cpp \
    arrow.cpp \
    connector.cpp \
    block_data.cpp

HEADERS += \
        dialog.h \
    block.h \
    myscene.h \
    arrow.h \
    connector.h \
    str_switch.h \
    block_data.h

FORMS += \
        dialog.ui
