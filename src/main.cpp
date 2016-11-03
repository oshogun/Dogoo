#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include "Map.h"
#include <stdlib.h>
#include <cstring>
#include <time.h>

// TEMPORARY SHIT:
Map map(15,15);
Tile brickType(TileTypes::BRICK);
Tile floorType(TileTypes::FLOOR);

sf::RenderWindow window;
sf::Texture tileset;
sf::Texture creatureSprites;
// Drawing a map for testing purposes

// TODO this is temporary and just for test:
// this entire file is temporary and just for test

void generateMap(sf::Vector2i playerStartingPos) 
{
    for (auto i = 0; i < 15; i++)
        for (auto j = 0; j < 15; j++) {
            map.setTileAt(i, j, brickType);
        }
    for (auto i = 1; i < 14; i++) {
        for (auto j = 1; j < 14; j++) {
            map.setTileAt(i, j, floorType);
        }
    }
    // Zoeira da geração procedural.
    srand(time(NULL));
    int nObjects = (int)(rand() % 8);
    int nWalls = (int)((rand() % 32) + 8);
    bool valid = false;
     for(auto i = 0; i < nWalls; i++) {
        int objX, objY;
        while (!valid) {                       
            objX = (int)((rand() + 1) % 14);
            objY = (int)((rand() + 1) % 14);
            if(&map.getTileAt(objX + 1, objY) == &brickType
                && &map.getTileAt(objX + 2, objY) == &brickType) {
                valid = false;
            }
            if(&map.getTileAt(objX, objY + 1) == &brickType 
                && &map.getTileAt(objX, objY + 2) == &brickType) {
                valid = false;
            }
            if((&map.getTileAt(objX, objY + 1) == &brickType 
                && &map.getTileAt(objX + 1, objY) == &brickType  || 
                (&map.getTileAt(objX, objY-1) == &brickType 
                && &map.getTileAt(objX -1 , objY) == &brickType )))  {
                valid = false;
            }
            if (&map.getTileAt(objX - 1, objY - 1) == &brickType ||
                &map.getTileAt(objX - 1, objY + 1) == &brickType ||
                &map.getTileAt(objX + 1, objY - 1) == &brickType ||
                &map.getTileAt(objX + 1, objY + 1) == &brickType) {
                valid = false;
            }   
            if (objX == playerStartingPos.x && objY == playerStartingPos.y) {
                valid = false;
            } else {
                valid = true;
            }           
            
        }
        valid = false;
        map.setTileAt(objX,objY,brickType);
    }

    valid = false;

    for(auto i = 0; i < nObjects; i++) {
        int objX, objY;
        while (!valid) {                       
            objX = (int)((rand() + 1) % 14);
            objY = (int)((rand() + 1) % 14);
            
            if(map.getTileAt(objX,objY).getOccupable()) {
                valid = true;
                if(map.getTileAt(objX + 1, objY).getContainsObject() 
                    && map.getTileAt(objX + 2, objY).getContainsObject()) {
                    valid = false;
                }
                if(map.getTileAt(objX, objY + 1).getContainsObject() 
                    && map.getTileAt(objX, objY + 2).getContainsObject()) {
                    valid = false;
                }
                if((map.getTileAt(objX, objY + 1).getContainsObject()
                    && map.getTileAt(objX + 1, objY).getContainsObject()) || 
                    (map.getTileAt(objX, objY-1).getContainsObject() 
                    && map.getTileAt(objX -1 , objY).getContainsObject()))  {
                    valid = false;
                }
                if (map.getTileAt(objX - 1, objY - 1).getContainsObject() ||
                    map.getTileAt(objX - 1, objY + 1).getContainsObject() ||
                    map.getTileAt(objX + 1, objY - 1).getContainsObject() ||
                    map.getTileAt(objX + 1, objY + 1).getContainsObject()) {
                    valid = false;
                }   
                if (objX == playerStartingPos.x && objY == playerStartingPos.y) {
                    valid = false;
                }           
            }
        }
        valid = false;
        map.getTileAt(objX,objY).setContainsObject(true);
    }
}

void printMap() 
{
    for (auto i = 0; i < 15; i++) {

        for (auto j = 0; j < 15; j++) {
            std::cout << map.getTileAt(i,j).getCurrentAscii();
            if (j == 14) std::cout << "\n";
        }

    }
}

void drawMap() {
    for (auto i = 0; i < 15; i++) {
            for (auto j = 0; j < 15; j++) {
            sf::Sprite layer1 = map.getTileAt(i, j).getSprite();
            layer1.setPosition(sf::Vector2f(j * 24, i * 24));
            if (!map.getTileAt(i,j).getOccupable() && map.getTileAt(i,j).getType() != TileTypes::BRICK)
                layer1.setColor(sf::Color::Green);
            window.draw(layer1);
        }
    }
}




void processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    map.movePlayer(Directions::NORTH);
                    std::cout << map.getPlayerPosition().x << "," << map.getPlayerPosition().y << "\n";
                    break;
                case sf::Keyboard::Down:
                    map.movePlayer(Directions::SOUTH);
                    std::cout << map.getPlayerPosition().x << "," << map.getPlayerPosition().y << "\n";
                    break;
                case sf::Keyboard::Left:
                    map.movePlayer(Directions::WEST);
                    std::cout << map.getPlayerPosition().x << "," << map.getPlayerPosition().y << "\n";
                    break;
                case sf::Keyboard::Right:
                    map.movePlayer(Directions::EAST);
                    std::cout << map.getPlayerPosition().x << "," << map.getPlayerPosition().y << "\n";
                    break;
                case sf::Keyboard::Escape:
                    window.close();
            }
        }
    }
}

// Use for GUI output
int guiMain()
{
    if (!tileset.loadFromFile("resources/sprites/2.png")) {
        throw std::runtime_error("Failed to load assets");
    }
    if (!creatureSprites.loadFromFile("resources/sprites/5.png")) {
        throw std::runtime_error("Failed to load assets");
    }
    sf::Sprite sprite_brick(tileset, sf::IntRect(1,37,8,8));
    sprite_brick.setScale(3,3);
    sf::Sprite sprite_floor(tileset, sf::IntRect(1,46,8,8));
    sprite_floor.setScale(3,3);

    sf::Sprite playerSprite(creatureSprites, sf::IntRect(2, 19, 8, 8));
    playerSprite.setScale(3,3);
    Tile brick(TileTypes::BRICK);
    Tile floor(TileTypes::FLOOR);
    brickType.setSprite(sprite_brick);
    floorType.setSprite(sprite_floor);
    brickType.setOccupable(false);
    floorType.setOccupable(true);
    generateMap(sf::Vector2i(6,6));
    map.setPlayerPosition(6,6);
    window.create(sf::VideoMode(360,360), "Dogoo", sf::Style::Titlebar);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > sf::seconds(1.f / 60.f)) { // GLORIOUS 60FPS MASTER RACE
            timeSinceLastUpdate -= sf::seconds(1.f / 60.f);
            processEvents();
        } 
        
        window.clear();
        drawMap();
        sf::Sprite layer2 = playerSprite;
        layer2.setPosition(sf::Vector2f(map.getPlayerPosition().y * 24, map.getPlayerPosition().x * 24));
        window.draw(layer2);
        window.display();
    }
    return 0;
}

// Use for console Output
int consoleMain()
{   
    brickType.setAscii('#');
    floorType.setAscii('.');
    brickType.setOccupable(false);
    floorType.setOccupable(true);
    generateMap(sf::Vector2i(7,7));
    bool done = false;
    map.setPlayerPosition(7,7);
    map.getTileAt(10,10).setContainsObject(true);
    while(!done) {
        system("clear"); // hella temporary
        printMap();
        std::cout << "Command? ";
        std::string command;
        std::cin >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (command == "north" || command == "n" || command == "up") {
            map.movePlayer(Directions::NORTH);
        } else if (command == "south" || command == "s" || command == "down") {
            map.movePlayer(Directions::SOUTH);
        } else if (command == "east" || command == "e" || command == "right") {
            map.movePlayer(Directions::EAST);
        } else if (command == "west" || command == "w" || command == "left") {
            map.movePlayer(Directions::WEST);
        } else if (command == "exit" || command == "quit" || command == "q") {
            done = true;
        } else {
            std::cout << "Invalid command\n";
        }
        std::cout << '\n';

    }
}

int main(int argc, char** argv)
{
    int returnValue;
    if (argc != 2) {
        returnValue = guiMain();
    } else if (argc == 2 && !strcmp(argv[1], "cli")) {
        returnValue = consoleMain();
    } else {
        std::cout << "Invalid parameters " << std::endl;
        return -1;
    }

    return returnValue;
}
	
    
    


