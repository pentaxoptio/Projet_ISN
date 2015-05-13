#ifndef BUTTON_H
#define BUTTON_H 

#include <string>
#include <functional>

#include "Gui.h"
#include "Textures.h"
#include "Fonts.h"

namespace gui
{
	//Classe Button
	//* Composant graphique qui peut être activé à la souris
	class Button : public Component
	{
		public :
			//Un bouton prend un paramètre "toggle". Si il vaut false, alors le bouton appelera une fonction au moment de son activation. Sinon, il restera activé et récupèrera la gestion des évènements du Container.
			Button(bool toggle, TextureHolder const &textures);
			Button(bool toggle, std::string const &text, sf::Font const &font, TextureHolder const &textures);

			//Les fonctions héritées de Component
			virtual bool isSelectable() const;
			virtual void handleEvent(sf::Event const &event);
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			virtual sf::Vector2f getSize() const;

			virtual void select();
			virtual void deselect();
			virtual void activate();
			virtual void deactivate();

			//Des fonctions permettant de définir ses caractéristiques
			void setText(std::string const &text);
			void setFont(sf::Font const &font);
			void setToggle(bool toggle);
			void setCallback(std::function<void()> callback);
			void initSprite();

		private :
			//Le bouton prend une référence constant vers les textures car il possède un sprite
			TextureHolder const& m_textures;
			sf::Sprite m_sprite;
			//Le texte du bouton
			sf::Text m_text;
			//Il s'agit d'une fonction qui sera appelée lors de son activation.
			std::function<void()> m_callback;
			bool m_toggle;
	};
}

#endif
