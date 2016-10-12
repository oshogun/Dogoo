#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include "Map.h"

// TEMPORARY SHIT:

sf::RenderWindow window;
sf::Texture tileset; // DERP
Map map(32,32);

// Drawing a map for testing purposes

// TODO this is temporary and just for test:
// this entire file is temporary and just for test
void generateMap()
{
    
    if (!tileset.loadFromFile("resources/sprites/2.png")) {
        throw std::runtime_error("Fuck you");
        std::cout << "wtf\n";
    }
    sf::Sprite sprite_brick(tileset, sf::IntRect(1,37,8,8));
    sprite_brick.setScale(3,3);
    sf::Sprite sprite_floor(tileset, sf::IntRect(1,46,8,8));
    sprite_floor.setScale(3,3);
    Tile brick(TileTypes::BRICK);
    Tile floor(TileTypes::FLOOR);
    brick.setSprite(sprite_brick);
    floor.setSprite(sprite_floor);
    
    for (int i = 0; i < 32; i++) {
        map.setTileAt(0,i,brick);
        map.setTileAt(23,i,brick);

    }
    for (int i = 0; i < 23; i++) {
        map.setTileAt(i,0,brick);
        map.setTileAt(i,31,brick);
    }
    for (int i = 1; i < 31; i++) {
        for (int j = 1; j < 23; j++) {
            map.setTileAt(j,i,floor);
        }
    }
}

void drawMap(unsigned rows, unsigned cols)
{   
    // NOW WE CAN DRAW KEWL MAPZZZ!!!!!!!!!!!!!!!!!!!!!!
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sf::Sprite temp = map.getTileAt(i,j).getSprite();
            temp.setPosition(sf::Vector2f(j * 24, i * 24)); 
            window.draw(temp);
        }
    }
    
}

int main()
{
   

    window.create(sf::VideoMode(800,600), "Teste", sf::Style::Titlebar);
	generateMap();
    while (window.isOpen()) {
	    sf::Event event;
	 	while (window.pollEvent(event)) {
	 		if (event.type == sf::Event::Closed)
 			    window.close();
 	    }
        window.clear(sf::Color::Black);
        drawMap(32,32);
	    window.display(); 
    }
	
    
    

	return 0;
}
