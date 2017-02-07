#-------------------------------------------------
#
# Project created by QtCreator 2015-09-01T22:22:04
#
#-------------------------------------------------

QT       += core gui
QT += webkit
QT += webkitwidgets

qmake:

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = haiNavigo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    downloaditem.cpp

HEADERS  += mainwindow.h \
    downloaditem.h

FORMS    +=

RESOURCES += \
    source.qrc

