#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>

#include "StateStack.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PlayMenuState.h"
#include "OpeningState.h"

#include "Textures.h"
#include "Fonts.h"

class App
{
    public :
        App();
        void run();

    private :
        void handleEvents();
        void update(sf::Time dt);
        void render();

		void registerStates();
		void registerTextures();

    private :
        sf::RenderWindow m_w;
        TextureHolder m_textures;
		FontHolder m_fonts;
		StateStack m_stack;
};

#endif
