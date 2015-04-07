#include "App.h"

App::App() :
	m_w(sf::VideoMode(640, 480), "DONJON")
	, m_textures()
	, m_fonts()
	, m_dungeon()
	, m_renderer(m_dungeon, {&m_w, &m_textures, &m_fonts})
{
    m_textures.registerTexture(Tiles, "res/tex/tiles.png");
	m_textures.registerRect(Air, sf::IntRect(0, 0, 24, 24));
	m_textures.registerRect(Wall, sf::IntRect(24, 0, 24, 24));
	m_textures.registerRect(Stairs, sf::IntRect(48, 0, 24, 24));
    m_textures.registerTexture(Player, "res/tex/player.png");
    m_textures.registerTexture(Effects, "res/tex/effects.png");
	m_textures.registerRect(RedEffect, sf::IntRect(0, 0, 24, 24));
	m_textures.registerTexture(Buttons, "res/tex/buttons.png");
	m_textures.registerRect(ButtonNormal, sf::IntRect(0, 0, 200, 50));
	m_textures.registerRect(ButtonSelect, sf::IntRect(0, 50, 200, 50));
	m_textures.registerRect(ButtonActivate, sf::IntRect(0, 100, 200, 50));
}

void App::run()
{
	sf::Clock clock;
	while (m_w.isOpen())
	{
		sf::Time dt = clock.restart();
		handleEvents();
		update(dt);
		render();
	}
}

void App::handleEvents()
{
	sf::Event event;
	while (m_w.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_w.close();
		else if (event.type == sf::Event::MouseMoved)
			m_renderer.onMouseMove(event.mouseMove);
		else if (event.type == sf::Event::Resized) //permet Ã  la fenÃªtre de garder une vue fixe mÃªme si elle est redimensionnÃ©e (par dÃ©faut, transforme la vue pour l'adapter au nouveau cadre)
			m_w.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
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
				default :
					break;
			}
		}
	}
}

void App::update(sf::Time)
{
	
}

void App::render()
{
	m_w.clear(sf::Color(20, 8, 30));
	m_w.draw(m_renderer);
	m_w.display();
}

