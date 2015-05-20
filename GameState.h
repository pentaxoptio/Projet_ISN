#ifndef GAMESTATE_H
#define GAMESTATE_H 

#include "State.h"
#include "Dungeon.h"
#include "DungeonRenderer.h"
#include "Gui.h"
#include "Label.h"

//Classe GameState
//* Cette classe est la classe qui gère le jeu en lui-même : elle possède le donjon ainsi que le DungeonRenderer
class GameState : public State
{
	public :
		GameState(StateStack &stack, Context context);

		//Fonctions héritées de State
		virtual void render();
		virtual bool update(sf::Time dt);
		//Ici, le GameState propose au joueur de changer les RenderSettings du DungeonRenderer avec les touches + et - (zoom) et de se déplacer avec les flèches directionnelles
		virtual bool handleEvent(sf::Event const& event);

		//Ces fonctions permettent au DungeonRenderer de demander à ce que le joueur se déplace ou attaque dans le donjon. C'est le GameState qui vérifie alors la possibilité de ces actions.
		void requestPlayerMove(sf::Vector2u newPos);
		void requestPlayerAttack(sf::Vector2u target);

	private :
		Dungeon m_dungeon;
		DungeonRenderer m_renderer;
        gui::Container m_container;
        gui::Label* m_life;
};

#endif
