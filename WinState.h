#ifndef WINSTATE_H
#define WINSTATE_H 

#include "State.h"
#include "Gui.h"
#include "Button.h"

//Classe WinState
//* Ce State s'active lorsque le joueur arrive à l'escalier. Elle affiche simplement un bouton intitulé "Next Level"
class WinState : public State
{
	public :
		WinState(StateStack &stack, Context context);

		virtual void render();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(sf::Event const& event);

	private :
		//Le container pour le bouton
		gui::Container m_container;
};

#endif
