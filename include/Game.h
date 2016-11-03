#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "Tile.h"
#include "Player.h"
#include "Map.h"
#include <vector>
#include <memory>

enum Tilesets { TILEMAP, SPRITES, PORTAL }
class Game {

public:
	Game();
	

private:
	void generateMap(unsigned rows, unsigned cols);
	void loadTilesets();
	ResourceHolder<sf::Texture, Tilesets> tileSetHolder;
	std::vector<Map> maps;
	// std::vector<Monster> mobs; not implemented yet
	Map currentMap;
	Map previousMap;
	Player player;



	// Map townMap; I'm not worrying about this now

};