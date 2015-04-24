#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H 

#include "State.h"
#include "Gui.h"
#include "Button.h"

class MainMenuState : public State
{
	public :
		MainMenuState(StateStack &stack, Context context);

		virtual void render();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(sf::Event const& event);

	private :
		sf::Sprite m_bg;
		gui::Container m_container;
};

#endif
