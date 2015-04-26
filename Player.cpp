#include "Player.h"

Player::Player() :
	m_maxHealth(100)
	, m_health(m_maxHealth)
	, m_position(0, 0)
{
	
}

void Player::setPosition(sf::Vector2u pos)
{
	m_position = pos;
}

sf::Vector2u Player::getPosition() const
{
	return m_position;
}
