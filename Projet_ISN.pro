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
SOURCE += main.cpp /

SOURCES += \
    main.cpp \
    App.cpp \
    Button.cpp \
    Dungeon.cpp \
    DungeonRenderer.cpp \
    Ennemy.cpp \
    Fonts.cpp \
    GameState.cpp \
    Gui.cpp \
    Label.cpp   \
    MainMenuState.cpp   \
    OpeningState.cpp    \
    Player.cpp  \
    PlayMenuState.cpp   \
    State.cpp   \
    StateStack.cpp  \
    Textures.cpp    \
    WinState.cpp \

HEADERS += \
    App.h \
    Button.h \
    Dungeon.h \
    DungeonRenderer.h \
    Ennemy.h \
    Fonts.h \
    GameState.h \
    Gui.h \
    Label.h   \
    MainMenuState.h   \
    OpeningState.h    \
    Player.h  \
    PlayMenuState.h   \
    State.h   \
    StateStack.h  \
    Textures.h    \
    EventManager.h \
    WinState.h \

