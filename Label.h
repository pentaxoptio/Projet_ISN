#ifndef LABEL_H
#define LABEL_H 

#include <string>

#include "Gui.h"

namespace gui
{
	class Label : public Component
	{
		public :
			Label();
			Label(std::string const &text, sf::Font const &font, unsigned int fontSize = 30);

			virtual bool isSelectable() const;
			virtual void handleEvent(sf::Event const &event);
			virtual sf::Vector2f getSize() const;

			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

			void setText(std::string const &string);
			void setFont(sf::Font const &font);
			void setColor(sf::Color color);

		private :
			sf::Text m_text;
	};
}

#endif
