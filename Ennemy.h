#ifndef ENNEMY_H
#define ENNEMY_H 

#include <SFML/Graphics.hpp>

enum EnnemyType
{
	Zombie,
};

class Ennemy
{
	public :
		Ennemy(EnnemyType type);

		void takeDamage(unsigned int dmg);

		EnnemyType getType() const;
		void setPosition(sf::Vector2u pos);
		sf::Vector2u getPosition() const;
		unsigned int getHealth() const;

	private :
		void initializeParametersAfterType();

	private :
		EnnemyType m_type;
		unsigned int m_maxHealth;
		unsigned int m_health;
		sf::Vector2u m_position;
};

#endif
