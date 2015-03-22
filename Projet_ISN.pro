TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++0x
QMAKE_CXXFLAGS += -lsfml-graphics
QMAKE_CXXFLAGS += -lsfml-system
QMAKE_CXXFLAGS += -L/usr/lib/x86_64-linux-gnu
QMAKE_CXXFLAGS += -I/usr/include
LIBS += -L"/home/michel/Projects/SFML/lib"
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
INCLUDEPATH += "/home/michel/Projects/SFML/include"
DEPENDPATH += "/home/michel/Projects/SFML/include"


SOURCES += main.cpp \
    App.cpp \
    Dungeon.cpp \
    DungeonRenderer.cpp \
    Textures.cpp

HEADERS += \
    App.h \
    Dungeon.h \
    DungeonRenderer.h \
    Utils.h \
    Textures.h
