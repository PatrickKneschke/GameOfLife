TARGET  = gameoflife

TEMPLATE = app
QT	+= widgets

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += gameoflife.h ui_gameoflife.h board.h
SOURCES += main.cpp gameoflife.cpp board.cpp
