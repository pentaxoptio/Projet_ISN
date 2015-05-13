#ifndef TEXTURES_H
#define TEXTURES_H 

#include <string>
#include <SFML/Graphics.hpp>

//Représente les différentes textures disponibles
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

//Représentes les différentes "parties" des textures disponibles
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

//Classe TextureHolder
//* Cette classe est un gestionnaire de textures mais aussi de rectangles : elle permet de charger des fichiers images sous forme de sf::Texture et permet également d'enrgistrer des rectangles correspondant à une partie de la texture (sprite), ce qui permet de stocker plusieurs sprites sur une seule image.
class TextureHolder
{
	public :
		TextureHolder();
		~TextureHolder();
		//Charge le fichier image en enregistre la texture sous une sf::Texture, associée à son identifiant de type TextureId
		void registerTexture(TextureId id, std::string filename);
		//Retourne la texture selon son identifiant
		sf::Texture const& getTexture(TextureId id) const;
		//Enrigistre l'association entre un rectangle de texture et son identifiant
		void registerRect(RectId id, sf::IntRect rect);
		//Retourne le rectangle correspondant à l'identifiant
		sf::IntRect getRect(RectId id) const;

	private :
		//Associations entre les sf::Texture et leur identifiants (TextureId), de même pour les rectangles (sf::IntRect et RectId)
		std::map<TextureId, sf::Texture*> m_textures;
		std::map<RectId, sf::IntRect> m_rects;
};

#endif
