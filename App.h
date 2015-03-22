#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "Dungeon.h"
#include "DungeonRenderer.h"
#include "Textures.h"

class App
{
    public :
        App();
        void run();

    private :
        void handleEvents();
        void update(sf::Time dt);
        void render();

    private :
        sf::RenderWindow m_w;
        TextureHolder m_textures;
        Dungeon m_dungeon;
        DungeonRenderer m_renderer;
};

#endif
