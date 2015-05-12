#include "WinState.h"

WinState::WinState(StateStack &stack, Context context) :
	State(stack, context)
{
	gui::Button* next = new gui::Button(false, "Next level", context.fonts->get(Default), *context.textures);
	next->setPosition(300, 150);
	next->setCallback([this] ()
	{
			accessGlobalSettings().level += 1;
			requestStackClear();
			requestStackPush(Game);
	});
	m_container.pack(next);
}

void WinState::render()
{
	sf::RectangleShape bg(getContext().window->getView().getSize());
	bg.setFillColor(sf::Color(0, 0, 0, 127));
	getContext().window->draw(bg);
	getContext().window->draw(m_container);
}

bool WinState::update(sf::Time)
{
	return true;
}

bool WinState::handleEvent(sf::Event const &event)
{
	m_container.handleEvent(event);
	return false;
}
