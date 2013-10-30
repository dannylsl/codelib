#-------------------------------------------------
#
# Project created by QtCreator 2013-07-15T13:35:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clientca
TEMPLATE = app

LIBS += -lssl -lcrypto

SOURCES += main.cpp\
        mainwindow.cpp


HEADERS  += mainwindow.h \
    certreq.h \
    clientca.h

FORMS    += mainwindow.ui
