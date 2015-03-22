#include "Dungeon.h"

Dungeon::Dungeon() :
	m_grid(Grid(12, std::vector<Keep::Tile>(8, Keep::Wall)))
	, m_player(6, 4)
{
	for (unsigned int i(3); i<=9; ++i)
		for (unsigned int j(2); j<=6; ++j)
			m_grid[i][j] = Keep::Air;
	m_grid[5][4] = Keep::Stairs;
	//Code de michel
}

void Dungeon::playerMove(unsigned int x, unsigned int y)
{
	m_player.x = x;
	m_player.y = y;
	//Ici TimothÃ© gÃ¨re les actions des ennemis
}

void Dungeon::playerMove(sf::Vector2u newPos)
{
	playerMove(newPos.x, newPos.y);
}

sf::Vector2u Dungeon::getSize() const
{
	return sf::Vector2u((unsigned int)m_grid.size(), (unsigned int)m_grid[0].size());
}

Keep::Tile Dungeon::getTile(unsigned int x, unsigned int y) const
{
	return m_grid[x][y];
}

sf::Vector2u Dungeon::getPlayerPosition() const
{
	return m_player;
}
