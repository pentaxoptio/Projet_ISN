#include "Button.h"
#include <iostream>

using namespace gui;

Button::Button(bool toggle, TextureHolder const &textures) :
	m_textures(textures)
	, m_sprite()
	, m_text()
	, m_callback()
	, m_toggle(toggle)
{
	std::cout << "construction button" << std::endl;
}

Button::Button(bool toggle, std::string const &text, sf::Font const &font, TextureHolder const &textures) :
	m_textures(textures)
	, m_sprite()
	, m_text(text, font)
	, m_callback()
	, m_toggle(toggle)
{
	std::cout << "construction button" << std::endl;
	m_text.setCharacterSize(20);
	m_text.setColor(sf::Color::White);
}

bool Button::isSelectable() const
{
	return true;
}

void Button::handleEvent(sf::Event const&)
{
	
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_sprite, states);
	target.draw(m_text, states);
}

sf::Vector2f Button::getSize() const
{
	return sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height);
}

void Button::select()
{
	Component::select();
	m_sprite.setTextureRect(m_textures.getRect(ButtonSelect));
}

void Button::deselect() 
{
	Component::deselect();
	m_sprite.setTextureRect(m_textures.getRect(ButtonNormal));
}

void Button::activate()
{
	Component::activate();
	if (m_toggle)
		m_sprite.setTextureRect(m_textures.getRect(ButtonActivate));
	if (m_callback)
		m_callback();
	if (!m_toggle)
		deactivate();
}

void Button::deactivate()
{
	Component::deactivate();
	if (m_toggle)
	{
		if (isSelected())
			m_sprite.setTextureRect(m_textures.getRect(ButtonSelect));
		else
			m_sprite.setTextureRect(m_textures.getRect(ButtonNormal));
	}
}

void Button::setText(std::string const &text)
{
	m_text.setString(text);
	m_text.setPosition(sf::Vector2f(0, 0));
}

void Button::setFont(sf::Font const &font)
{
	m_text.setFont(font);
}

void Button::setToggle(bool toggle)
{
	m_toggle = toggle;
}

void Button::setCallback(std::function<void()> callback)
{
	m_callback = callback;
}

void Button::initSprite()
{
	m_sprite.setTexture(m_textures.getTexture(Buttons));
	m_sprite.setTextureRect(m_textures.getRect(ButtonNormal));
}
