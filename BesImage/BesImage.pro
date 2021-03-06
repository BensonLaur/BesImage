#-------------------------------------------------
#
# Project created by QtCreator 2018-06-28T14:57:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BesImage
#TEMPLATE = subdirs          #配置TEMPLATE为subdirs设置多工程

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=$$PWD absFiles
include(absFiles/absFiles.pri)

INCLUDEPATH +=$$PWD topWidget
include(topWidget/topwidget.pri)

INCLUDEPATH +=$$PWD middleWidget
include(middleWidget/middleWidget.pri)

INCLUDEPATH +=$$PWD printWidget
include(printWidget/printWidget.pri)



SOURCES += main.cpp\
        mainwindow.cpp \
    appConfig.cpp

HEADERS  += mainwindow.h \
    global.h \
    appConfig.h

DISTFILES +=


RESOURCES += \
    res_topwidget.qrc \
    res_main.qrc \
    res_middlewidget.qrc \
#    res_traymenu.qrc\
#    res_bottomwidget.qrc
