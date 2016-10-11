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