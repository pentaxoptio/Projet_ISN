#ifndef BUTTON_H
#define BUTTON_H 

#include <string>
#include <functional>

#include "Gui.h"
#include "Textures.h"
#include "Fonts.h"

namespace gui
{
	class Button : public Component
	{
		public :
			Button(bool toggle, TextureHolder const &textures);
			Button(bool toggle, std::string const &text, sf::Font const &font, TextureHolder const &textures);

			virtual bool isSelectable() const;
			virtual void handleEvent(sf::Event const &event);
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			virtual sf::Vector2f getSize() const;

			virtual void select();
			virtual void deselect();
			virtual void activate();
			virtual void deactivate();

			void setText(std::string const &text);
			void setFont(sf::Font const &font);
			void setToggle(bool toggle);
			void setCallback(std::function<void()> callback);
			void initSprite();

		private :
			TextureHolder const& m_textures;
			sf::Sprite m_sprite;
			sf::Text m_text;
			std::function<void()> m_callback;
			bool m_toggle;
	};
}

#endif
