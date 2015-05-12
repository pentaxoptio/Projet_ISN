#ifndef DUNGEONRENDERER_H
#define DUNGEONRENDERER_H

#include <SFML/Graphics.hpp>
#include <exception>

#include "Dungeon.h"
#include "Utils.h"

class GameState;

struct RenderConfig
{
    float tileSize;
};

enum MaskTile
{
	Hidden,
	Dark,
	Visible
};

class DungeonRenderer : public sf::Drawable
{
    public :
        DungeonRenderer(Dungeon const& dungeon, Context context, GameState& game);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time dt);
        void onMouseMove(sf::Event::MouseMoveEvent event);
        void onMouseButtonPressed(sf::Event::MouseButtonEvent event);
		void onPlayerMove();

		void setRenderConfig(RenderConfig newConf);
		RenderConfig getRenderConfig() const;

        sf::Vector2f getSize() const;

    private :
        sf::Vector2u determineTile(sf::Vector2i location) const;

	private :
		typedef std::vector<std::vector<MaskTile> > Mask;

    private :
        Dungeon const& m_dungeon;
        RenderConfig m_conf;
		Mask m_mask; //Masque permettant de mettre le noir / gris
        Context m_context;
		GameState& m_game; //référence vers la GameState (nécessaire pour traiter les events)
        bool m_hasHoverTile;
        sf::Vector2u m_hoverTile;
		sf::Time m_elapsedTime;
		sf::Vector2u m_previousPlayerPosition; //Utile pour le masque (voir onPlayerMove)
		RectId m_heroRect;
};

#endif
