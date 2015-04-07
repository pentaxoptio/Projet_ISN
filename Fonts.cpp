#include "Fonts.h"

#include <iostream>

FontHolder::FontHolder() :
	m_fonts()
{
	std::cout << "construction fonts" << std::endl;
}

FontHolder::~FontHolder()
{
	for (std::pair<FontId, sf::Font*> pair : m_fonts)
		delete pair.second;
}

void FontHolder::registerFont(FontId id, std::string filename)
{
	sf::Font* newFont = new sf::Font;
	newFont->loadFromFile(filename);
	m_fonts.insert(std::make_pair(id, newFont));
}

sf::Font const& FontHolder::get(FontId id)
{
	return *m_fonts[id];
}
