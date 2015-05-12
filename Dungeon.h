#ifndef DUNGEON_H
#define DUNGEON_H

#include "Player.h"
#include "Ennemy.h"
#include "Utils.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace Keep
{
    enum Tile
    {
        Air,
        Wall,
        Stairs
    };
}

typedef std::vector<std::vector<Keep::Tile> > Grid;

class Dungeon
{
    public :
        Dungeon(Difficulty diff);
        void playerMove(unsigned int x, unsigned int y);
        void playerMove(sf::Vector2u newPos);

        sf::Vector2u getSize() const;
        Keep::Tile getTile(unsigned int x, unsigned int y) const;
        sf::Vector2u getPlayerPosition() const;
		std::vector<Ennemy> const& getEnnemies() const;

	private :
		void placeRooms(int roomsCount);
		void createWay(int x, int y, int xDest, int yDest);
		void connect(std::vector<int> xPositions, std::vector<int> yPositions);
        std::vector<int> dontGetOutX(int depart, std::vector<int> direction);
        std::vector<int> dontGetOutY(int depart, std::vector<int> direction);
        void diagonal(int xPosition, int yPosition, int xDirection, int yDirection);
        void setDifficulty(Difficulty diff);
        void placeEnnemy(int nbrEnnemy);
		//intelligence artificielle
		void ia();
		Grid traitementUD(Grid detection);
		Grid traitementRL(std::vector<Keep::Tile> detection, int portee, std::vector<Keep::Tile> detectionUp, std::vector<Keep::Tile> detectionDown);
		std::vector<Grid> traitementDia(Grid detectionUp, Grid detectionDown, std::vector<Keep::Tile> detectionRight, std::vector<Keep::Tile> detectionLeft);
		std::vector<int> traitementLimites(int posX, int posY, int d);
		void moveEnnemies(unsigned int ennemyIndex, Grid detectionUp, Grid detectionDown, std::vector<Keep::Tile> detectionRight, std::vector<Keep::Tile> detectionLeft);
		
    private :
        Grid m_grid;
        Player m_player;
		std::vector<Ennemy> m_ennemies;
};

#endif
