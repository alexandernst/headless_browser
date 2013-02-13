QT += network
QT -= gui

CONFIG += console
CONFIG += c++11

HEADERS += ../socket-ipc/client/client.h
SOURCES += main.cpp ../socket-ipc/client/client.cpp
