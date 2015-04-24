#ifndef GAMESTATE_H
#define GAMESTATE_H 

#include "State.h"
#include "Dungeon.h"
#include "DungeonRenderer.h"

class GameState : public State
{
	public :
		GameState(StateStack &stack, Context context);

		virtual void render();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(sf::Event const& event);

	private :
		Dungeon m_dungeon;
		DungeonRenderer m_renderer;
};

#endif
