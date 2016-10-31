#include "Map.h"

Map::Map(const unsigned _rows, const unsigned _collumns):
	rows(_rows), 
	collumns(_collumns),
	tileMap(_rows, std::vector<Tile>(_collumns))
{
}



Tile & Map::getTileAt(unsigned row, unsigned col)
{
	return tileMap[row][col];
}

void Map::setTileAt(unsigned row, unsigned col, const Tile & tile)
{
	tileMap[row][col] = tile;
}

unsigned Map::getRows() 
{
	return rows;
}

unsigned Map::getCollumns()
{
	return collumns;
}

std::vector<std::vector<Tile>> Map::getMap()
{
	return tileMap;
}

sf::Vector2i Map::getPlayerPosition() {
	return playerPosition;
}

void Map::setPlayerPosition(int x, int y) {
	playerPosition.x = x;
	playerPosition.y = y;

	getTileAt(playerPosition.x,playerPosition.y).setContainsPlayer(true);
}

void Map::movePlayer (Directions direction) {
	int oldPosX = playerPosition.x;
	int oldPosY = playerPosition.y;

	switch (direction) {
		case Directions::NORTH:
			if (oldPosX - 1 >= 0) 
				if (tileMap[oldPosX - 1][oldPosY].getOccupable())
					playerPosition.x--;
			break;
		case Directions::SOUTH:
			if (oldPosX + 1 < tileMap.size())
				if (tileMap[oldPosX + 1][oldPosY].getOccupable())
					playerPosition.x++;
			break;
		case Directions::WEST:
			if(oldPosY -1 >= 0)
				if (tileMap[oldPosX][oldPosY - 1].getOccupable())
					playerPosition.y--;
			break;
		case Directions::EAST:
			if (oldPosY + 1 < tileMap[0].size())
				if (tileMap[oldPosX][oldPosY + 1].getOccupable())
					playerPosition.y++;
			break;
	}
		tileMap[oldPosX][oldPosY].setContainsPlayer(false);
		tileMap[playerPosition.x][playerPosition.y].setContainsPlayer(true);
}	
	
