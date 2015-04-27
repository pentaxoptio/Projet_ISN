#ifndef OPENINGSTATE_H
#define OPENINGSTATE_H 

#include "State.h"

class OpeningState : public State
{
	public :
		OpeningState(StateStack& stack, Context context);
		
		virtual bool handleEvent(sf::Event const& event);
		virtual bool update(sf::Time dt);
		virtual void render();

	private :
		sf::Sprite m_logo;
		sf::Time m_lifetime;
};

#endif
