#ifndef DUNGEON_H
#define DUNGEON_H

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
        Grid m_grid;
        sf::Vector2u m_player;
};

#endif
