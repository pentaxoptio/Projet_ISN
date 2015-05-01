#ifndef DUNGEONRENDERER_H
#define DUNGEONRENDERER_H

#include <SFML/Graphics.hpp>
#include <exception>

#include "Dungeon.h"
#include "Utils.h"

struct RenderConfig
{
    float tileSize;
};

class DungeonRenderer : public sf::Drawable, public sf::Transformable
{
    public :
        DungeonRenderer(Dungeon const& dungeon, Context context);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void update(sf::Time dt);
        void onMouseMove(sf::Event::MouseMoveEvent event);
        void onMouseButtonPressed(sf::Event::MouseButtonEvent event);

		void setRenderConfig(RenderConfig newConf);
		RenderConfig getRenderConfig() const;

        sf::Vector2f getSize() const;

    private :
        sf::Vector2u determineTile(sf::Vector2i location) const;

    private :
        Dungeon const& m_dungeon;
        RenderConfig m_conf;
        Context m_context;
        bool m_hasHoverTile;
        sf::Vector2u m_hoverTile;
		sf::Time m_elapsedTime;
		RectId m_heroRect;
};

#endif
