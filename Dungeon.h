#ifndef DUNGEON_H
#define DUNGEON_H

#include "Player.h"

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
        Dungeon();
        void playerMove(unsigned int x, unsigned int y);
        void playerMove(sf::Vector2u newPos);

        sf::Vector2u getSize() const;
        Keep::Tile getTile(unsigned int x, unsigned int y) const;
        sf::Vector2u getPlayerPosition() const;

	private :
		void placeRooms(int roomsCount);
		void createWay(int x, int y, int xDest, int yDest);
		void connect(std::vector<int> xPositions, std::vector<int> yPositions);

    private :
        Grid m_grid;
        Player m_player;
};

#endif
