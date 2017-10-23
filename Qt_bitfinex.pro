#-------------------------------------------------
#
# Project created by QtCreator 2017-09-07T13:26:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_bitfinex
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    updaterdialog.cpp \
    BitfinexAPI.cpp \
    example.cpp \
    menu/currencymenu.cpp \
    menu/currencymenucell.cpp

HEADERS  += widget.h \
    updaterdialog.h \
    BitfinexAPI.hpp \
    menu/currencymenu.h \
    menu/currencymenucell.h

FORMS    += widget.ui \
    menu/currencymenu.ui \
    menu/currencymenucell.ui

LIBS += -lcrypto++ -lcurl
