#include "DungeonRenderer.h"
#include <iostream>

DungeonRenderer::DungeonRenderer(Dungeon const& dungeon, Context context) :
	m_dungeon(dungeon)
	, m_conf({48.f})
	, m_context(context)
	, m_hasHoverTile(false)
	, m_hoverTile(0, 0)
{
	
}

void DungeonRenderer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	sf::Vector2f scales(m_conf.tileSize/24.f, m_conf.tileSize/24.f);
	
	sf::Sprite sWall(m_context.textures->getTexture(Tiles), m_context.textures->getRect(Wall));
	sWall.setScale(scales);
	sf::Sprite sAir(m_context.textures->getTexture(Tiles), m_context.textures->getRect(Air));
	sAir.setScale(scales);
	sf::Sprite sStairs(m_context.textures->getTexture(Tiles), m_context.textures->getRect(Stairs));
	sStairs.setScale(scales);
	sf::Sprite sPlayer(m_context.textures->getTexture(Player));
	sPlayer.setScale(scales);
	sf::Sprite sRedEffect(m_context.textures->getTexture(Effects), m_context.textures->getRect(RedEffect));
	sRedEffect.setScale(scales);

	sf::Vector2u player = m_dungeon.getPlayerPosition();
	sf::Vector2f winCenter = m_context.window->getView().getCenter();
	//LL'origine des cases est en leur centre :
	sf::Vector2f origin(12.f, 12.f);
	sWall.setOrigin(origin);
	sAir.setOrigin(origin);
	sStairs.setOrigin(origin);
	sPlayer.setOrigin(sf::Vector2f(12.f, 24.f));
	sRedEffect.setOrigin(origin);

	//Case en haut Ã  gauche, Ã  partir de laquelle on va calculer le rendu:
	sf::Vector2f upLeft(winCenter.x - (float)player.x*m_conf.tileSize,
			winCenter.y - (float)player.y*m_conf.tileSize);

	for (unsigned int i(0); i<m_dungeon.getSize().x; ++i)
		for (unsigned int j(0); j<m_dungeon.getSize().y; ++j)
		{
			sf::Vector2f pos(upLeft.x + (float)i*m_conf.tileSize,
					upLeft.y + (float)j*m_conf.tileSize);
			switch (m_dungeon.getTile(i, j))
			{
				case Keep::Wall :
					sWall.setPosition(pos);
					target.draw(sWall);
					break;
				case Keep::Air :
					sAir.setPosition(pos);
					target.draw(sAir);
					break;
				case Keep::Stairs :
					sStairs.setPosition(pos);
					target.draw(sStairs);
				default :
					break;
			}
			
			if (m_hasHoverTile && m_hoverTile.x == i && m_hoverTile.y == j)
			{
				sRedEffect.setPosition(pos);
				target.draw(sRedEffect);
			}	
			
			if (i == player.x && j == player.y)
			{
				sPlayer.setPosition(pos);
				target.draw(sPlayer);
			}
		}
}

void DungeonRenderer::onMouseMove(sf::Event::MouseMoveEvent event)
{
	sf::Vector2u player = m_dungeon.getPlayerPosition();
	sf::Vector2u eventPos(0, 0);
	try
	{
		eventPos = determineTile(sf::Vector2i(event.x, event.y));
	}
    catch (std::runtime_error)
	{
		m_hasHoverTile = false;
		return;
	}
	//On a donc selectionnÃ© une case valide
	m_hoverTile = eventPos;
	sf::Vector2<long> distToPlayer((long)player.x - (long)m_hoverTile.x, (long)player.y - (long)m_hoverTile.y);
	if (distToPlayer.x >= -1 && distToPlayer.x <= 1 && distToPlayer.y >= -1 && distToPlayer.y <= 1)
		m_hasHoverTile = true;
	else
		m_hasHoverTile = false;
}

void DungeonRenderer::onMouseButtonPressed(sf::Event::MouseButtonEvent event)
{
	if (event.button == sf::Mouse::Left)
	{
		if (m_hasHoverTile)
		{
			
		}
	}
}

void DungeonRenderer::setRenderConfig(RenderConfig newConf)
{
	m_conf = newConf;
}

RenderConfig DungeonRenderer::getRenderConfig() const
{
	return m_conf;
}

sf::Vector2f DungeonRenderer::getSize() const
{
	return sf::Vector2f((float)m_dungeon.getSize().x*m_conf.tileSize, (float)m_dungeon.getSize().y*m_conf.tileSize);
}

sf::Vector2u DungeonRenderer::determineTile(sf::Vector2i location) const
{
	sf::Vector2u player = m_dungeon.getPlayerPosition();
	sf::Vector2f winCenter = m_context.window->getView().getCenter();
	sf::Vector2f upLeft(winCenter.x - ((float)player.x + 0.5f)*m_conf.tileSize,
			winCenter.y - ((float)player.y + 0.5f)*m_conf.tileSize);
	sf::Vector2i eventRelativePos(location.x - (int)upLeft.x, location.y - (int)upLeft.y);

	if (eventRelativePos.x >= 0 && eventRelativePos.x < (int)getSize().x && eventRelativePos.y >= 0 && eventRelativePos.y < (int)getSize().y)
		return sf::Vector2u(eventRelativePos.x/(int)m_conf.tileSize, eventRelativePos.y/(int)m_conf.tileSize);
	throw std::runtime_error("oob");
}

