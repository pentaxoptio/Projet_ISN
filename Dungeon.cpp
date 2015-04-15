#include "Dungeon.h"
#include <time.h>
#include <stdlib.h>

Dungeon::Dungeon() :
	m_grid()
	, m_player(6, 4)
{
	int roomsCount = 16; //à modifier
	std::srand((unsigned int)std::time(0));
	int width = rand() % 25 + 75,
		height = rand() % 15 + 50;
	m_grid = Grid(width, std::vector<Keep::Tile>(height, Keep::Wall));
	placeRooms(roomsCount);
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

//Creation de donjon
void Dungeon::placeRooms(int roomsCount)
{
	std::vector<sf::IntRect> rooms;
	std::vector<int> xRooms;
	std::vector<int> yRooms;
	int cpt(0);
	
	while (cpt < roomsCount)
	{
		//Génération de la position et de la taille de la salle
		int xPosition = rand() % (int)m_grid.size();
		int yPosition = rand() % (int)m_grid[0].size();
		int xPositionMax = xPosition + rand()%5 + 7; 
		int yPositionMax = yPosition + rand()%5 + 7;
		
		if ((unsigned int)xPositionMax > m_grid.size()) //salle sort de la grille
			continue;
		if ((unsigned int)yPositionMax + 1 > m_grid[0].size())
			continue;
		
		sf::IntRect newRoom(xPosition, yPosition, xPositionMax-xPosition+1, yPositionMax-yPosition+1);
		
		bool intersect = false;
		if (rooms.size() > 0)
		{
			for (sf::IntRect room : rooms)
				if (newRoom.intersects(room))
					intersect = true;
		}
		
		if (!intersect)
		{
			rooms.push_back(newRoom);
			xRooms.push_back(newRoom.left);
			yRooms.push_back(newRoom.top);
			++cpt;
		}
		else
		{
			continue;
		}
		
		for (int x(xPosition); x < xPositionMax; ++x)
			for (int y(yPosition); y < yPositionMax; ++y)
				m_grid[x][y] = Keep::Air;
	} //end while
	
	connect(xRooms, yRooms);
}

void Dungeon::createWay(int x, int y, int xDest, int yDest)
{
	int xDiff = xDest - x;
	int yDiff = yDest - y;
	int xDetour = rand()%5 + 5;
	int yDetour = rand()%5 + 5;
	int x1 = x-1;
	int y1 = y-1;
	int max = 0; //nombre max de 1 et de -1 dans une liste. Permet a une liste de continuer alors que l'autre est finie
	
	if (xDiff+xDetour > yDiff + yDetour)
		max = xDiff + xDetour;
	else
		max = yDiff + yDetour;
	
	std::vector<int> xCoords;
	for (int cpt(0); cpt < xDiff; ++cpt)
		xCoords.push_back(1);
	for (int cpt(0); cpt < xDetour; ++cpt)
	{
		xCoords.push_back(1);
		xCoords.push_back(-1);
	}
	
	std::vector<int> yCoords;
	for (int cpt(0); cpt < yDiff; ++cpt)
		yCoords.push_back(1);
	for (int cpt(0); cpt < yDetour; ++cpt)
	{
		yCoords.push_back(1);
		yCoords.push_back(-1);
	}
	
	while (xCoords.size() > yCoords.size())
		yCoords.push_back(0);
	while (yCoords.size() > xCoords.size())
		xCoords.push_back(0);
	
	std::random_shuffle(xCoords.begin(), xCoords.end());
	std::random_shuffle(yCoords.begin(), yCoords.end());
	
	m_grid[x1][y1] = Keep::Air;
	for (int cpt(0); cpt <= xCoords.size(); ++cpt)
	{
		if (cpt < xCoords.size())
			x1 += xCoords[cpt];
		
		if (cpt < yCoords.size())
			y1 += yCoords[cpt];
		
		m_grid[x1][y1] = Keep::Air;
	}
}

void Dungeon::connect(std::vector<int> xPositions, std::vector<int> yPositions)
{
	int moitie = (int)std::floor((double)xPositions.size()*0.5);
	std::vector<int> unMoit;
	std::vector<int> deuxMoit;
	
	for (int cpt(0); cpt < moitie; ++cpt)
		unMoit.push_back(cpt);
	for (int cpt(moitie); cpt<2*moitie; ++cpt)
		deuxMoit.push_back(cpt);
	
	std::random_shuffle(unMoit.begin(), unMoit.end());
	std::random_shuffle(deuxMoit.begin(), deuxMoit.end());
	int cpt(0);
	while (cpt < moitie)
	{
		createWay(xPositions[unMoit[cpt]], yPositions[unMoit[cpt]], xPositions[deuxMoit[cpt]], yPositions[deuxMoit[cpt]]);
		++cpt;
	}
	
	if (2*(unsigned int)moitie < xPositions.size())
		createWay((int)xPositions.size(), (int)yPositions.size(), xPositions[2], yPositions[2]); //remplacer 2 par un nombre random
}
