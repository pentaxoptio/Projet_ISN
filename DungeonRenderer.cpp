#include "DungeonRenderer.h"
#include <iostream>
#include "GameState.h"

DungeonRenderer::DungeonRenderer(Dungeon const& dungeon, Context context, GameState& game) :
	m_dungeon(dungeon) ,
	m_conf({48.f, false}) ,
	m_mask(dungeon.getSize().x, std::vector<MaskTile>(dungeon.getSize().y, Hidden)) ,
	m_context(context) ,
	m_game(game) ,
	m_hasHoverTile(false) ,
	m_hoverTile(0, 0) ,
	m_elapsedTime(sf::Time::Zero) ,
	m_heroRect(Player1)
{
	onPlayerMove(); //permet de mettre à jour le mask;
}

void DungeonRenderer::draw(sf::RenderTarget& target, sf::RenderStates) const
{
	sf::Vector2f scales(m_conf.tileSize/24.f, m_conf.tileSize/24.f);
	
	sf::Sprite sWall(m_context.textures->getTexture(Tiles), m_context.textures->getRect(Wall));
	sWall.setScale(scales);
	sf::Sprite sAir(m_context.textures->getTexture(Tiles), m_context.textures->getRect(Air));
	sAir.setScale(scales);
	sf::Sprite sStairs(m_context.textures->getTexture(Tiles), m_context.textures->getRect(Stairs));
	sStairs.setScale(scales);
	sf::Sprite sPlayer(m_context.textures->getTexture(Hero), m_context.textures->getRect(m_heroRect));
	sPlayer.setScale(scales);
	sf::Sprite sRedEffect(m_context.textures->getTexture(Effects), m_context.textures->getRect(RedEffect));
	sRedEffect.setScale(scales);
	sf::RectangleShape sDarkTile(sf::Vector2f(24.f, 24.f));
	sDarkTile.setScale(scales);
	sDarkTile.setFillColor(sf::Color(0, 0, 0, 127));

	//AFFICHER LES COORD DE CHAQUE CASE -> sera rendu seulement si configuré pour
	sf::Text sText("", m_context.fonts->get(Default), 10);
	sText.setOrigin(sf::Vector2f(22.f, 5.f));

	sf::Vector2u player = m_dungeon.getPlayerPosition();
	sf::Vector2f winCenter = m_context.window->getView().getCenter();
	//LL'origine des cases est en leur centre :
	sf::Vector2f origin(12.f, 12.f);
	sWall.setOrigin(origin);
	sAir.setOrigin(origin);
	sStairs.setOrigin(origin);
	sPlayer.setOrigin(sf::Vector2f(12.f, 24.f));
	sRedEffect.setOrigin(origin);
	sDarkTile.setOrigin(origin);

	//Case en haut Ã  gauche, Ã  partir de laquelle on va calculer le rendu:
	sf::Vector2f upLeft(winCenter.x - (float)player.x*m_conf.tileSize,
			winCenter.y - (float)player.y*m_conf.tileSize);

	for (unsigned int i(0); i<m_dungeon.getSize().x; ++i)
		for (unsigned int j(0); j<m_dungeon.getSize().y; ++j)
		{
			if (m_mask[i][j] != Hidden)
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
				//AFFICHER LES COORDS DE CHAQUE CASE
				if (m_conf.renderCoords)
				{
					sText.setPosition(pos);
					sText.setString("[" + std::to_string(i) + "; " + std::to_string(j) + "]");
					target.draw(sText);
				}

				//si grisée, la case est ... ben grisée ^^
				if (m_mask[i][j] == Dark)
				{
					sDarkTile.setPosition(pos);
					target.draw(sDarkTile);
				}
			}
		}
}

void DungeonRenderer::update(sf::Time dt)
{
	m_elapsedTime += dt;
	if (m_elapsedTime >= sf::milliseconds(700))
	{
		 m_elapsedTime = sf::Time::Zero;
		 if (m_heroRect == Player1)
			 m_heroRect = Player2;
		 else
			 m_heroRect = Player1;
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

void DungeonRenderer::onPlayerMove()
{
	sf::Vector2u player = m_dungeon.getPlayerPosition();
	sf::Vector2u upLeft;
	if (player.x - 5 >= m_dungeon.getSize().x)
		upLeft.x = 0;
	else
		upLeft.x = player.x - 5;
	if (player.y - 5 >= m_dungeon.getSize().y)
		upLeft.y = 0;
	else
		upLeft.y = player.y - 5;
	std::cout << "upLeft : (" << upLeft.x << "; " << upLeft.y << ")" << std::endl;
	
	for (unsigned int i(upLeft.x); i < player.x + 5; ++i)
	{
		for (unsigned int j(upLeft.y); j < player.y + 5; ++j)
		{
			if (i < m_dungeon.getSize().x && j < m_dungeon.getSize().y) // i et j ne sortent pas des limites
				m_mask[i][j] = Visible;
		}
	}
	
	std::cout << "playerMove fini !" << std::endl;
}

void DungeonRenderer::onMouseButtonPressed(sf::Event::MouseButtonEvent event)
{
	if (event.button == sf::Mouse::Left)
	{
		if (m_hasHoverTile)
		{
			m_game.requestPlayerMove(m_hoverTile);
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

