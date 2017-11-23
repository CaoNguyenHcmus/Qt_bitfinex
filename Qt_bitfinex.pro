#-------------------------------------------------
#
# Project created by QtCreator 2017-09-07T13:26:37
#
#-------------------------------------------------
#to_string is not a member of std
CONFIG	+= c++11
# QT += network for QSslSocket (file julyhttp.h)
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_bitfinex
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    updaterdialog.cpp \
    BitfinexAPI.cpp \
    example.cpp \
    menu/currencymenu.cpp \
    menu/currencymenucell.cpp \
    julyhttp.cpp \
    exchange_bitfinex.cpp \
    exchange.cpp \
    logthread.cpp \
    currencypairitem.cpp \
    depthitem.cpp \
    indicatorengine.cpp \
    iniengine.cpp

HEADERS  += widget.h \
    updaterdialog.h \
    BitfinexAPI.hpp \
    menu/currencymenu.h \
    menu/currencymenucell.h \
    julyhttp.h \
    main.h \
    exchange_bitfinex.h \
    exchange.h \
    logthread.h \
    currencypairitem.h \
    currencyinfo.h \
    depthitem.h \
    indicatorengine.h \
    iniengine.h

FORMS    += widget.ui \
    menu/currencymenu.ui \
    menu/currencymenucell.ui

LIBS += -lcrypto++ -lcurl -lz
# LIBS += -llibssl

RESOURCES += \
    QtResource.qrc