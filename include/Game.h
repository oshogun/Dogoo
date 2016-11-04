#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "Tile.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <memory>
#include <iostream>
#include <map>

enum Tilesets { TILEMAP, SPRITES, PORTAL };
enum Sprites {BRICK_SPRITE, FLOOR_SPRITE};
class Game {

public:
	Game();
	void generateMap(unsigned rows, unsigned cols);
	void moveToNextMap();
	// Debug functions:
	void printCurrentMap();
	void printPreviousMap();

private:
	void loadTilesets();
	unsigned mapCount;
	ResourceHolder<sf::Texture, Tilesets> tileSetHolder;
	std::vector<std::shared_ptr<Map>> maps;
	std::vector<sf::Sprite> sprites;
	std::shared_ptr<Map> currentMap;
	std::shared_ptr<Map>  previousMap;
	// std::vector<Monster> mobs; not implemented yet
	Player player;
	std::map<Sprites, Tile> tiles;
	


	// Map townMap; I'm not worrying about this now

};