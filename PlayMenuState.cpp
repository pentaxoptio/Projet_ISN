#include "PlayMenuState.h"

PlayMenuState::PlayMenuState(StateStack &stack, Context context) :
	State(stack, context) ,
	m_bg(context.textures->getTexture(TitleScreen)) ,
	m_container() ,
	m_difficultyButton(nullptr) ,
	m_difficulty(Normal)
{
	gui::Label* diffLabel = new gui::Label("Difficulty :", context.fonts->get(Default));
	diffLabel->setPosition(100, 250);
	diffLabel->setColor(sf::Color::Black);
	m_container.pack(diffLabel);

	gui::Button* difficulty = new gui::Button(false, "Normal", context.fonts->get(Default), *context.textures);
	difficulty->setPosition(120 + diffLabel->getSize().x, 250);
	difficulty->setCallback([this] ()
	{
		if (m_difficulty == Normal)
		{
			m_difficulty = Hard;
			m_difficultyButton->setText("Hard");
		}
		else if (m_difficulty == Hard)
		{
			m_difficulty = Easy;
			m_difficultyButton->setText("Easy");
		}
		else
		{
			m_difficulty = Normal;
			m_difficultyButton->setText("Normal");
		}
	});
	m_container.pack(difficulty);
	m_difficultyButton = difficulty;

	gui::Button* play = new gui::Button(false, "Play", context.fonts->get(Default), *context.textures);
	play->setPosition(100, 350);
	play->setCallback([this] ()
	{
		accessGlobalSettings().difficulty = m_difficulty;
		requestStackPop();
		requestStackPush(Game);
	});
	m_container.pack(play);

	gui::Button* cancel = new gui::Button(false, "Cancel", context.fonts->get(Default), *context.textures);
	cancel->setPosition(100, 400);
	cancel->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(MainMenu);
	});
	m_container.pack(cancel);
}

bool PlayMenuState::handleEvent(sf::Event const& event)
{
    //délégation
	m_container.handleEvent(event);
	return true;
}

bool PlayMenuState::update(sf::Time)
{
	return true;
}

void PlayMenuState::render()
{
	sf::Vector2f scale(
			(float)getContext().window->getSize().x / m_bg.getLocalBounds().width,
			(float)getContext().window->getSize().y / m_bg.getLocalBounds().height);
	m_bg.setScale(scale);

	sf::RenderWindow& window = *getContext().window;
	window.draw(m_bg);
	window.draw(m_container);
}
