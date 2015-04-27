#include "OpeningState.h"

OpeningState::OpeningState(StateStack& stack, Context context) :
	State(stack, context)
	, m_logo(context.textures->getTexture(Logo))
	, m_lifetime(sf::milliseconds(5000))
{
	
}

bool OpeningState::handleEvent(sf::Event const&)
{
	//lol
	return true;
}

bool OpeningState::update(sf::Time dt)
{
	m_lifetime -= dt;
	if (m_lifetime <= sf::Time::Zero)
	{
		requestStackPop();
		requestStackPush(MainMenu);
	}
	return true;
}

void OpeningState::render()
{
	sf::Vector2f scale(
			(float)getContext().window->getSize().x / m_logo.getLocalBounds().width,
			(float)getContext().window->getSize().y / m_logo.getLocalBounds().height);
	m_logo.setScale(scale);

	sf::RenderWindow &window = *getContext().window;
	window.draw(m_logo);
}
