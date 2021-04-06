#-------------------------------------------------
#
# Project created by QtCreator 2020-11-14T14:08:28
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myserialport
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += "D:\1azrrecourse\APROJECT\Aproject\IFP_3000_QT_Test\SerialTest\inc" \
               "D:\1azrrecourse\APROJECT\Aproject\IFP_3000_QT_Test\SerialTest\ui"

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
UI_DIR=./ui

SOURCES += \
    src/demozoom.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mycombobox.cpp \
    src/testchart.cpp

HEADERS += \
    inc/demozoom.h \
    inc/mainwindow.h \
    inc/mycombobox.h \
    inc/testchart.h \

FORMS += \
    ui/mainwindow.ui
