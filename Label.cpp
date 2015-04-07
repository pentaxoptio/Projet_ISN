#include "Label.h"

#include <iostream>

using namespace gui;

Label::Label() :
	m_text()
{
	std::cout << "construction label" << std::endl;
}

Label::Label(std::string const &text, sf::Font const &font, unsigned int fontSize) :
	m_text(text, font, fontSize)
{
	
}

bool Label::isSelectable() const
{
	return false;
}

void Label::handleEvent(sf::Event const&)
{
	
}

sf::Vector2f Label::getSize() const
{
	return sf::Vector2f(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_text, states);
}

void Label::setText(std::string const &string)
{
	m_text.setString(string);
}

void Label::setFont(sf::Font const &font)
{
	m_text.setFont(font);
}

void Label::setColor(sf::Color color)
{
	m_text.setColor(color);
}
