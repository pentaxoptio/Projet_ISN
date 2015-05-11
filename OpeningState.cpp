#include "OpeningState.h"

OpeningState::OpeningState(StateStack& stack, Context context) :
	State(stack, context) ,
	m_logo(context.textures->getTexture(Logo)) ,
	m_lifetime(sf::milliseconds(3500))
{
	
}

bool OpeningState::handleEvent(sf::Event const&)
{
	return false;
}

bool OpeningState::update(sf::Time dt)
{
	m_lifetime -= dt;
	if (m_lifetime <= sf::milliseconds(1000))
	{
		unsigned char alpha = (unsigned char)(255 * ((float)m_lifetime.asMilliseconds()) / (float)1000);
		m_logo.setColor(sf::Color(255, 255, 255, alpha));
	}
	if (m_lifetime <= sf::Time::Zero)
	{
		requestStackPop();
	}
	return false;
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
