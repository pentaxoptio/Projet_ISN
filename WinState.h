#ifndef WINSTATE_H
#define WINSTATE_H 

#include "State.h"
#include "Gui.h"
#include "Button.h"

class WinState : public State
{
	public :
		WinState(StateStack &stack, Context context);

		virtual void render();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(sf::Event const& event);

	private :
		gui::Container m_container;
};

#endif
