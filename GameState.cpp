#include "GameState.h"
#include <iostream>

GameState::GameState(StateStack &stack, Context context) :
	State(stack, context) ,
    m_dungeon(getGlobalSettings().difficulty) ,
	m_renderer(m_dungeon, context, *this)
{
	
}

void GameState::render()
{
	getContext().window->draw(m_renderer);
}

bool GameState::update(sf::Time dt)
{
	m_renderer.update(dt);
	return true;
}

bool GameState::handleEvent(sf::Event const& event)
{
	if (event.type == sf::Event::MouseMoved)
		m_renderer.onMouseMove(event.mouseMove);
	else if (event.type == sf::Event::MouseButtonPressed)
		m_renderer.onMouseButtonPressed(event.mouseButton);
	else if (event.type == sf::Event::KeyPressed)
	{
		sf::Vector2u pos;
		RenderConfig conf = m_renderer.getRenderConfig();
		switch (event.key.code)
		{
			case sf::Keyboard::Add :
				if (conf.tileSize < 192.f)
					conf.tileSize = conf.tileSize*2.f;
				m_renderer.setRenderConfig(conf);
				break;
			case sf::Keyboard::Subtract :
				if (conf.tileSize > 6.f)
					conf.tileSize = conf.tileSize/2.f;
				m_renderer.setRenderConfig(conf);
				break;
			case sf::Keyboard::Up :
				pos = m_dungeon.getPlayerPosition();
				if (pos.y > 0)
					pos.y -= 1;
				requestPlayerMove(pos);
				break;
			case sf::Keyboard::Down :
				pos = m_dungeon.getPlayerPosition();
				if (pos.y+1 < m_dungeon.getSize().y)
					pos.y += 1;
				requestPlayerMove(pos);
				break;
			case sf::Keyboard::Right :
				pos = m_dungeon.getPlayerPosition();
				if (pos.x+1 < m_dungeon.getSize().x)
					pos.x += 1;
				requestPlayerMove(pos);
				break;
			case sf::Keyboard::Left :
				pos = m_dungeon.getPlayerPosition();
				if (pos.x > 0)
					pos.x -= 1;
				requestPlayerMove(pos);
				break;
			default :
				break;
		}
	}

	return true; //lol
}

void GameState::requestPlayerMove(sf::Vector2u newPos)
{
	if (m_dungeon.getTile(newPos.x, newPos.y) == Keep::Air)
	{
		m_dungeon.playerMove(newPos);
		m_renderer.onPlayerMove(); //nécéssaire pour mettre à jour le masque
	}
	else if (m_dungeon.getTile(newPos.x, newPos.y) == Keep::Stairs)
	{
		//requestStackPush(WinState)
		requestStackPop();
		requestStackPush(MainMenu);
	}
}

void GameState::requestPlayerAttack(sf::Vector2u)
{
	//à compléter ^^
}
