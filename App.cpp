#include "App.h"

App::App() :
	m_w(sf::VideoMode(800, 450), "DONJON") ,
	m_textures() ,
	m_fonts() ,
	m_stack({&m_w, &m_textures, &m_fonts})
{
	registerStates();
	registerTextures();

	m_fonts.registerFont(Default, "res/font/SourceCodePro-Regular.ttf");

	m_stack.pushState(MainMenu);
	m_stack.pushState(Opening);
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
		else if (event.type == sf::Event::Resized)
			m_w.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
		m_stack.handleEvent(event);
	}
}

void App::update(sf::Time dt)
{
	m_stack.update(dt);
}

void App::render()
{
	m_w.clear(sf::Color(0, 0, 8));
	m_stack.render();
	m_w.display();
}

void App::registerStates()
{
	m_stack.registerState<OpeningState>(Opening);
	m_stack.registerState<MainMenuState>(MainMenu);
	m_stack.registerState<PlayMenuState>(PlayMenu);
	m_stack.registerState<GameState>(Game);
}

void App::registerTextures()
{
	m_textures.registerTexture(Tiles, "res/tex/tiles.png");
	m_textures.registerRect(Air, sf::IntRect(0, 0, 24, 24));
	m_textures.registerRect(Wall, sf::IntRect(24, 0, 24, 24));
	m_textures.registerRect(Stairs, sf::IntRect(48, 0, 24, 24));
    m_textures.registerTexture(Hero, "res/tex/player.png");
	m_textures.registerRect(Player1, sf::IntRect(0, 0, 24, 48));
	m_textures.registerRect(Player2, sf::IntRect(24, 0, 24, 48));
    m_textures.registerTexture(Effects, "res/tex/effects.png");
	m_textures.registerRect(RedEffect, sf::IntRect(0, 0, 24, 24));
	m_textures.registerTexture(Buttons, "res/tex/buttons.png");
	m_textures.registerRect(ButtonNormal, sf::IntRect(0, 0, 200, 40));
	m_textures.registerRect(ButtonSelect, sf::IntRect(0, 40, 200, 40));
	m_textures.registerRect(ButtonActivate, sf::IntRect(0, 80, 200, 40));
	m_textures.registerTexture(TitleScreen, "res/tex/title_screen.png");
	m_textures.registerTexture(Logo, "res/tex/logo.png");
	m_textures.registerTexture(Ennemies, "res/tex/zombie.png");
	m_textures.registerRect(Zombie1, sf::IntRect(0, 0, 24, 48));
	m_textures.registerRect(Zombie2, sf::IntRect(24, 0, 24, 48));
}
