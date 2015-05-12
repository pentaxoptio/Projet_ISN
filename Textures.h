#ifndef TEXTURES_H
#define TEXTURES_H 

#include <string>
#include <SFML/Graphics.hpp>

enum TextureId
{
	Tiles,
	Hero,
	Buttons,
	Effects,
	TitleScreen,
	Logo,
	Ennemies
};

enum RectId
{
	Wall,
	Air,
	Stairs,
	RedEffect,
	BlueEffect,
	ButtonNormal,
	ButtonSelect,
	ButtonActivate,
	Player1,
	Player2,
	Zombie1,
	Zombie2
};

class TextureHolder
{
	public :
		TextureHolder();
		~TextureHolder();
		void registerTexture(TextureId id, std::string filename);
		sf::Texture const& getTexture(TextureId id) const;
		void registerRect(RectId id, sf::IntRect rect);
		sf::IntRect getRect(RectId id) const;

	private :
		std::map<TextureId, sf::Texture*> m_textures;
		std::map<RectId, sf::IntRect> m_rects;
};

#endif
