QT += webkitwidgets widgets network
CONFIG(release, debug|release){
QT -= gui
}

CONFIG += console
CONFIG += c++11

HEADERS += nam.h daemon.h ../socket-ipc/server/server.h
SOURCES += main.cpp nam.cpp daemon.cpp ../socket-ipc/server/server.cpp

RESOURCES += resources.qrc
