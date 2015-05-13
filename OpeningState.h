#ifndef OPENINGSTATE_H
#define OPENINGSTATE_H 

#include "State.h"

class OpeningState : public State
{
	public :
		OpeningState(StateStack& stack, Context context);
        /* voir les autre states pour handleEvent et render*/
		virtual bool handleEvent(sf::Event const& event);

        /* entrée : sf::Time
         * sortie : false (boolean)
         * description : La fonction recupere l'heure a laquelle elle est lancée.
         * elle affiche la page de presentation
         * cependant des que ca fait plus d'une seconde que cette page est affichée elle se retire elle meme
         */
		virtual bool update(sf::Time dt);
		virtual void render();

	private :
		sf::Sprite m_logo;
		sf::Time m_lifetime;
};

#endif
