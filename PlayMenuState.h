#ifndef PLAYMENUSTATE_H
#define PLAYMENUSTATE_H 

#include "State.h"
#include "Gui.h"
#include "Button.h"
#include "Utils.h"

class PlayMenuState : public State
{
	public :
		PlayMenuState(StateStack &stack, Context context);

		virtual bool handleEvent(sf::Event const& event);
		virtual bool update(sf::Time dt);
		virtual void render();

	private :
		sf::Sprite m_bg;
		gui::Container m_container;
		gui::Button* m_difficultyButton; //On a besoin de le garder pour changer son texte
		Difficulty m_difficulty;
};

#endif
