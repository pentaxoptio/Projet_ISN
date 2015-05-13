#ifndef FONTS_H
#define FONTS_H 

#include <SFML/Graphics.hpp>
#include <string>

enum FontId
{
	Default
};

//Classe FontHolder
//* Gestionnaire de police(s) de caractères. Cette classe se charge de charger les fichiers en mémoires et de conserver la police (sous forme de sf::Font)
class FontHolder
{
	public :
		FontHolder();
		~FontHolder();
		//Enregistre une police en association avec son Id (FontId).
		void registerFont(FontId id, std::string filename);
		//Retourne la police demandée
		sf::Font const& get(FontId id);

	private :
		std::map<FontId, sf::Font*> m_fonts;
};

#endif
