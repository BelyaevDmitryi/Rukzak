#-------------------------------------------------
#
# Project created by QtCreator 2016-12-11T23:42:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab5
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    ruksak.h

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS += -std=gnu++11
CONFIG += c++11
CONFIG += c++14
