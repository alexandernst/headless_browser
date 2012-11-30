QT       += core gui webkit network

TARGET = hb

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    hb.cpp \
    nam.cpp

HEADERS += \
    hb.h \
    nam.h
