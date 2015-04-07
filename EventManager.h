#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H 

#include "DungeonRenderer.h"

class EventManager
{
	public :
		EventManager(sf::RenderWindow const& window, DungeonRenderer& renderer, Dungeon& dungeon);
		void handleEvents();

	private :
		void handleEvent(sf::Event event);

	private :
		sf::RenderWindow const& m_window;
		Dungeon& m_dungeon;
		DungeonRenderer& m_renderer;
};

#endif
