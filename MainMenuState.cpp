#include "MainMenuState.h"

MainMenuState::MainMenuState(StateStack &stack, Context context) :
	State(stack, context) ,
	m_bg(context.textures->getTexture(TitleScreen))
{
	gui::Button* play = new gui::Button(false, "Play", context.fonts->get(Default), *context.textures);
	play->setPosition(100, 300);
	play->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(PlayMenu);
	});
	m_container.pack(play);

	gui::Button* quit = new gui::Button(false, "Quit", context.fonts->get(Default), *context.textures);
	quit->setPosition(100,350);
	quit->setCallback([this] ()
	{
		getContext().window->close();
	});
	m_container.pack(quit);
}


void MainMenuState::render()
{
	sf::Vector2f scale(
			(float)getContext().window->getSize().x / m_bg.getLocalBounds().width,
			(float)getContext().window->getSize().y / m_bg.getLocalBounds().height);
	m_bg.setScale(scale);

	sf::RenderWindow &window = *getContext().window;
	//window.setView(window.getDefaultView());
	window.draw(m_bg);
	window.draw(m_container);
}

bool MainMenuState::update(sf::Time)
{
	return true;
}

bool MainMenuState::handleEvent(sf::Event const &event)
{
	//on délègue...
	m_container.handleEvent(event);
	return true;
}
