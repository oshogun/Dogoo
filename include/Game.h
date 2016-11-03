#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "Tile.h"
#include <vector>
class Game {
private:
	ResourceHolder<sf::Sprite,TileTypes> tileSetHolder;
	std::vector<Map> maps;
	
	Map currentMap;
	Map previousMap;
	Player player;

	// Map townMap; I'm not worrying about this now

};