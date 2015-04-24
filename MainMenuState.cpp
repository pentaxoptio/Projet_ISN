#include "MainMenuState.h"

MainMenuState::MainMenuState(StateStack &stack, Context context) :
	State(stack, context)
	, m_bg(context.textures->getTexture(TitleScreen))
{
	sf::Vector2f scale(
			(float)context.window->getSize().x / m_bg.getLocalBounds().width,
			(float)context.window->getSize().y / m_bg.getLocalBounds().height);
	m_bg.setScale(scale);

	gui::Button* play = new gui::Button(false, "Play", context.fonts->get(Default), *context.textures);
	play->setPosition(100, 300);
	play->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(Game);
	});
	m_container.pack(play);
}

void MainMenuState::render()
{
	sf::RenderWindow &window = *getContext().window;
	//window.setView(window.getDefaultView());
	window.draw(m_bg);
	window.draw(m_container);
}

bool MainMenuState::update(sf::Time)
{
	//lol
	return true;
}

bool MainMenuState::handleEvent(sf::Event const &event)
{
	//on délègue...
	m_container.handleEvent(event);
	return true;
}
