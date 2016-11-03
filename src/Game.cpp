#include "Game.h"

Game::Game() {
	loadTilesets();

}

void Game::loadTilesets() {
	tileSetHolder.load(TILEMAP, "resources/sprites/2.png");
	tileSetHolder.load(SPRITES, "resources/sprites/5.png");
	tileSetHolder.load(PORTAL, "resources/sprites/entrance.png");
	generateMap(14,14);
	
}

void Game::generateMap(unsigned rows, unsigned cols)
{
	currentMap.setRows(size.x);
	currentMap.setCollumns(size.y);
	Tile brickType(TileTypes::BRICK);
	Tile floorType(TileTypes::FLOOR);
	for (auto i = 0; i < size.x; i++)
        for (auto j = 0; j < size.x; j++) {
            currentMap.setTileAt(i, j, brickType);
        }
    for (auto i = 1; i < size.y - 1; i++) {
        for (auto j = 1; j < size.y - 1; j++) {
            currentMap.setTileAt(i, j, floorType);
        }
    }
}