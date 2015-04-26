#ifndef UTILS_H
#define UTILS_H 

#include <SFML/Graphics.hpp>

#include "Textures.h"
#include "Fonts.h"

struct Context
{
	sf::RenderWindow* window;
	TextureHolder* textures;
	FontHolder* fonts;
};

enum Difficulty
{
	Easy,
	Normal,
	Hard
};

#endif
