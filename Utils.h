#ifndef UTILS_H
#define UTILS_H 

#include <SFML/Graphics.hpp>

#include "Textures.h"
#include "Fonts.h"

//Cette structure est très utilisée car elle permet d'avoir un accès aux informations importantes du programme, notamment les ressources (textures et polices)
struct Context
{
	sf::RenderWindow* window;
	TextureHolder* textures;
	FontHolder* fonts;
};

//Cet enum représente la difficulté choisie par le joueur dans le GameMenuState.
enum Difficulty
{
	Easy,
	Normal,
	Hard
};

//Cette structure représente les paramètres du StateStack accesssibles par tous les States. Parmi ces paramètres on trouve le niveau de difficulté choisi par le joueur, l'étage actuellement parcouru (level) ainsi que le score.
struct GlobalSettings
{
	Difficulty difficulty;
	unsigned int level;
	unsigned int score;
};

#endif
