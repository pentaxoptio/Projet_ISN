#ifndef LABEL_H
#define LABEL_H 

#include <string>

#include "Gui.h"

namespace gui
{
	//Classe Label
	//* Un composant graphique très simple : il ne fait qu'afficher du texte
	class Label : public Component
	{
		public :
			Label();
			Label(std::string const &text, sf::Font const &font, unsigned int fontSize = 30);

			//Les fonctions héritées de Component
			virtual bool isSelectable() const;
			virtual void handleEvent(sf::Event const &event);
			virtual sf::Vector2f getSize() const;

			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

			//Les fonctions pour modifier le label
			void setText(std::string const &string);
			void setFont(sf::Font const &font);
			void setColor(sf::Color color);

		private :
			//Grâce à la SFML, un seul objet permet d'afficher du texte
			sf::Text m_text;
	};
}

#endif
