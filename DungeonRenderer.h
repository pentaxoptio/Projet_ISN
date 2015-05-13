#ifndef DUNGEONRENDERER_H
#define DUNGEONRENDERER_H

#include <SFML/Graphics.hpp>
#include <exception>

#include "Dungeon.h"
#include "Utils.h"

class GameState;

//Cette structure représente les paramètres nécessaires au rendu du donjon. En l'occurence il n'y en a qu'un : c'est la taille, en pixels, d'une case de donjon. Elle permet de définir le zoom. (utilisé dans le GameState)
struct RenderConfig
{
    float tileSize;
};

//Cet enum représente une case du masque de rendu. Ce masque se superpose au donjon et permet de ne pas faire apparaître les zone inexplorées et de griser les zones explorées mais éloignées. Une case du donjon peut donc apparaître cachée, assombrie ou totalement visible
enum MaskTile
{
	Hidden,
	Dark,
	Visible
};

//Classe DungoenRenderer
//* Cette classe sert d'intermédiaire entre le donjon (données brutes) et l'écran (affichage). Pour cela il se charge non seulement d'afficher le donjon mais aussi plus car il ajoute un effet de "brouillard de guerre" qui assombrit les zones inexplorées. De plus il traite les évènements, notamment de la souris en déterminant quelle case a été cliquée à partir des coordonnées en pixels.
class DungeonRenderer : public sf::Drawable
{
    public :
		//Le DungeonRenderer prend évidemment en paramètre le donjon en référence constante car il ne le modifie par directement. Il prend également le contexte pour avoir accès aux textures et une référence vers le GameState pour appeler des fonctions telles que "requestPlayerMove".
        DungeonRenderer(Dungeon const& dungeon, Context context, GameState& game);
		//Cette fonction permet d'afficher le donjon, en tenant compte du brouillard de guerre.
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time dt);
		//Ces deux fonctions traitens les évènements liés à la souris. Pour cela elles font appel à la fonction "determineTile" qui donne, à partir des coordonnées en pixels, la case du donjon cliquée (ou survolée).
        void onMouseMove(sf::Event::MouseMoveEvent event);
        void onMouseButtonPressed(sf::Event::MouseButtonEvent event);
		//Cette fonction prévient le DungeonRenderer que le joueur a bougé, et qu'il doit mettre à jour le brouillard de guerre
		void onPlayerMove();

		//Ces fonctions donnent accès et modification à la configuration du rendu, notamment pour le zoom.
		void setRenderConfig(RenderConfig newConf);
		RenderConfig getRenderConfig() const;

        sf::Vector2f getSize() const;

    private :
		//Cette fonction détermine, à partir des coordonnées sur la fenêtre en pixels, la case du donjon correspondante.
        sf::Vector2u determineTile(sf::Vector2i location) const;

	private :
		typedef std::vector<std::vector<MaskTile> > Mask;

    private :
		//Référence constante vers le donjon à afficher
        Dungeon const& m_dungeon;
		//Configuration du rendu
        RenderConfig m_conf;
		//Masque permettant de réaliser le "brouillard de guerre" : il s'agit pour chaque case de déterminer si elle est visible ou masquée
		Mask m_mask;
        Context m_context;
		GameState& m_game;
		//Ces deux variables membres permettent de stocker en mémoire si une case est survolée par la souris et laquelle
        bool m_hasHoverTile;
        sf::Vector2u m_hoverTile;
		//Temps écoulé (animation du joueur)
		sf::Time m_elapsedTime;
		//Position précédente du joueur : cela permet de griser les cases que le joueur a exploré
		sf::Vector2u m_previousPlayerPosition;
		//Rectangle de la texture nécessaire pour l'animation
		RectId m_heroRect;
};

#endif
