#ifndef PLAYER_H
#define PLAYER_H 

#include <SFML/Graphics.hpp>

class Player
{
	public :
		Player();
		
		void setPosition(sf::Vector2u pos);
		sf::Vector2u getPosition() const;

	private :
		unsigned int m_maxHealth;
		unsigned int m_health;
		sf::Vector2u m_position;
};

#endif
