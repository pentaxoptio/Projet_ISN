#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

#include "Textures.h"

struct Context
{
    sf::RenderWindow* window;
    TextureHolder* textures;
};

#endif
