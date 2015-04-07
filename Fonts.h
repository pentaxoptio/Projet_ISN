#ifndef FONTS_H
#define FONTS_H 

#include <SFML/Graphics.hpp>
#include <string>

enum FontId
{
	Default
};

class FontHolder
{
	public :
		FontHolder();
		~FontHolder();
		void registerFont(FontId id, std::string filename);
		sf::Font const& get(FontId id);

	private :
		std::map<FontId, sf::Font*> m_fonts;
};

#endif
