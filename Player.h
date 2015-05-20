#ifndef PLAYER_H
#define PLAYER_H 

#include <SFML/Graphics.hpp>

class Player
{
	public :
		Player();
        /* entrée : Vector2n. paire d'int qui corespondent a une coordonées
         * sortie : rien
         * description : permet de définir la position du joueur
         */
		void setPosition(sf::Vector2u pos);

        /* entrée : Vector2n. paire d'int qui corespondent a une coordonées
         * sortie : rien
         * description : permet de recuperer la position du joueur
         */
		sf::Vector2u getPosition() const;
        unsigned int getHealth() const;
        unsigned int getMaxHealth() const;

	private :
		unsigned int m_maxHealth;
		unsigned int m_health;
		sf::Vector2u m_position;
};

#endif
