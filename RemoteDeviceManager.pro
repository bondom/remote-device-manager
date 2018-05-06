#-------------------------------------------------
#
# Project created by QtCreator 2012-06-04T18:48:56
#
#-------------------------------------------------


TARGET = RemoteDeviceControl
TEMPLATE = app

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += main.cpp\
        mainwindow.cpp \
    connection_manager.cpp

HEADERS  += mainwindow.h \
    connection_manager.h

FORMS    += mainwindow.ui

LIBS += -lws2_32
