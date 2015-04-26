#include "GameState.h"
#include <iostream>

GameState::GameState(StateStack &stack, Context context) :
	State(stack, context)
	, m_dungeon()
	, m_renderer(m_dungeon, context)
{
	Difficulty dfclt = getGlobalSettings().difficulty;
	std::cout << "Difficulté choisie : ";
	if (dfclt == Easy)
		std::cout << "Easy";
	else if (dfclt == Normal)
		std::cout << "Normal";
	else
		std::cout << "Hard";
	std::cout << std::endl;
}

void GameState::render()
{
	getContext().window->draw(m_renderer);
}

bool GameState::update(sf::Time)
{
	return true; //lol
}

bool GameState::handleEvent(sf::Event const& event)
{
	if (event.type == sf::Event::MouseMoved)
		m_renderer.onMouseMove(event.mouseMove);
	else if (event.type == sf::Event::KeyPressed)
	{
		sf::Vector2u pos;
		switch (event.key.code)
		{
			case sf::Keyboard::Up :
				pos = m_dungeon.getPlayerPosition();
				if (pos.y > 0)
				{
					pos.y -= 1;
					m_dungeon.playerMove(pos);
				}
				break;
			case sf::Keyboard::Down :
				pos = m_dungeon.getPlayerPosition();
				if (pos.y < m_dungeon.getSize().y - 1)
				{
					pos.y += 1;
					m_dungeon.playerMove(pos);
				}
				break;
			case sf::Keyboard::Left :
				pos = m_dungeon.getPlayerPosition();
				if (pos.x > 0)
				{
					pos.x -= 1;
					m_dungeon.playerMove(pos);
				}
				break;
			case sf::Keyboard::Right :
				pos = m_dungeon.getPlayerPosition();
				if (pos.x < m_dungeon.getSize().x - 1)
				{
					pos.x += 1;
					m_dungeon.playerMove(pos);
				}
				break;
			case sf::Keyboard::Add :
				if (m_renderer.getRenderConfig().tileSize < 192.f)
					m_renderer.setRenderConfig({m_renderer.getRenderConfig().tileSize*2.f});
				break;
			case sf::Keyboard::Subtract :
				if (m_renderer.getRenderConfig().tileSize > 6.f)
					m_renderer.setRenderConfig({m_renderer.getRenderConfig().tileSize/2.f});
				break;
			default :
				break;
		}
	}

	return true; //lol
}
