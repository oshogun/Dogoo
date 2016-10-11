#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include "Map.h"
int main()
{
    sf::Texture tileset;
    if (!tileset.loadFromFile("resources/sprites/2.png")) {
        return -1;
    }
    sf::Sprite sprite(tileset, sf::IntRect(1,37,8,8));
	sprite.setScale(5,5);

    Tile brick1(TileTypes::BRICK);
    brick1.setSprite(sprite);
    Map map(32,32);
    for (int i = 0; i < 32; i++)
    {
        for(int j = 0; j < 32; j++)
        {
            map.setTileAt(i,j,brick1);
        }
    }

    sf::RenderWindow window(sf::VideoMode(800,600), "Teste");
	while (window.isOpen()) {
	    sf::Event event;
	 	while (window.pollEvent(event)) {
	 		if (event.type == sf::Event::Closed)
 			    window.close();
 	    }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                sf::Sprite temp = map.getTileAt(i,j).getSprite();
                temp.setPosition(j * 40, i * 40);
                window.draw(temp);
            }
        }
 	    // window.draw(map.getTileAt(0,0).getSprite());
      //   sf::Sprite temp = map.getTileAt(0,1).getSprite();
      //   temp.setPosition(sf::Vector2f(40, 0));
      //   window.draw(temp);
      //   temp = map.getTileAt(0,2).getSprite();
      //   temp.setPosition(sf::Vector2f(80,0));
      //   window.draw(temp);
	    window.display(); 
    }
	
    
    

	return 0;
}
