QT       += webkitwidgets widgets network

TARGET = hb

CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
    nam.cpp \
    headless_browser.cpp

HEADERS += \
    nam.h \
    headless_browser.h
