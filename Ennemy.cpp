#include "Ennemy.h"

Ennemy::Ennemy(EnnemyType type) :
	m_type(type)
	, m_maxHealth(0)
	, m_health(m_maxHealth)
	, m_position(0, 0)
{
	initializeParametersAfterType();
}

EnnemyType Ennemy::getType() const
{
	return m_type;
}

void Ennemy::setPosition(sf::Vector2u pos)
{
	m_position = pos;
}

sf::Vector2u Ennemy::getPosition() const
{
	return m_position;
}

void Ennemy::initializeParametersAfterType()
{
	switch (m_type)
	{
		case Zombie :
			m_maxHealth = 50;
			break;
	}

	m_health = m_maxHealth;
}
