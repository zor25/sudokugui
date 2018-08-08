#-------------------------------------------------
#
# Project created by QtCreator 2018-06-25T14:01:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sudokugui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    secwind.cpp
CONFIG += static.

HEADERS  += mainwindow.h \
    secwind.h

FORMS    += mainwindow.ui \
    secwind.ui

RESOURCES += \
    dfont.qrc
