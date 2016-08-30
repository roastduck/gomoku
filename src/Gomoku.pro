#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T09:51:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gomoku
TEMPLATE = app


SOURCES += main.cpp\
        gomoku.cpp \
    serverdialog.cpp \
    input.cpp \
    remoteinput.cpp \
    data.cpp

HEADERS  += gomoku.h \
    serverdialog.h \
    const.h \
    input.h \
    remoteinput.h \
    data.h

FORMS    += gomoku.ui \
    serverdialog.ui
