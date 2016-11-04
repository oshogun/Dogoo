#include "Game.h"

Game::Game():mapCount(0) {
	loadTilesets();
	Tile brickTile(TileTypes::BRICK);
	brickTile.setAscii('#');
	brickTile.setOccupable(false);
	Tile floorTile(TileTypes::FLOOR);
	floorTile.setAscii('.');
	floorTile.setOccupable(true);
	tiles.insert(std::make_pair(BRICK_SPRITE, brickTile));
	tiles.insert(std::make_pair(FLOOR_SPRITE, floorTile));

	generateMap(15,15);
	currentMap = maps[0];
}



void Game::generateMap(unsigned rows, unsigned cols)
{
	std::shared_ptr<Map> map(new Map(rows, cols));
	for (auto i = 0; i < rows; i++)
        for (auto j = 0; j < cols; j++) {
            map->setTileAt(i, j, tiles.find(BRICK_SPRITE)->second);
        }
    for (auto i = 1; i < rows - 1; i++) {
        for (auto j = 1; j < cols - 1; j++) {
            map->setTileAt(i, j, tiles.find(FLOOR_SPRITE)->second);
        }
    }
    maps.push_back(map);
    mapCount++;

}

void Game::loadTilesets() {
	tileSetHolder.load(TILEMAP, "resources/sprites/2.png");
	tileSetHolder.load(SPRITES, "resources/sprites/5.png");
	tileSetHolder.load(PORTAL, "resources/sprites/entrance.png");
}

void Game::printCurrentMap()
{
	for (auto i = 0; i < currentMap->getRows(); i++) {

        for (auto j = 0; j < currentMap->getCollumns(); j++) {
            std::cout << currentMap->getTileAt(i,j).getCurrentAscii();
            if (j == currentMap->getCollumns() - 1) std::cout << "\n";
        }

    }
}

void Game::printPreviousMap()
{
	for (auto i = 0; i < previousMap->getRows(); i++) {

        for (auto j = 0; j < previousMap->getCollumns(); j++) {
            std::cout << previousMap->getTileAt(i,j).getCurrentAscii();
            if (j == previousMap->getCollumns() - 1) std::cout << "\n";
        }

    }
}
void Game::moveToNextMap() 
{
	previousMap = currentMap;
	generateMap(10,10);
	currentMap = maps[mapCount - 1];
}