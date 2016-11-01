#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include "Map.h"
#include "stdlib.h"

// TEMPORARY SHIT:
Map map(15,15);
Tile brickType(TileTypes::BRICK);
Tile floorType(TileTypes::FLOOR);
// Drawing a map for testing purposes

// TODO this is temporary and just for test:
// this entire file is temporary and just for test
void printMap() 
{
    for (auto i = 0; i < 15; i++) {

        for (auto j = 0; j < 15; j++) {
            std::cout << map.getTileAt(i,j).getCurrentAscii();
            if (j == 14) std::cout << "\n";
        }

    }
}
int main()
{   
    brickType.setAscii('#');
    floorType.setAscii('.');
    brickType.setOccupable(false);
    floorType.setOccupable(true);
    for (auto i = 0; i < 15; i++)
        for (auto j = 0; j < 15; j++) {
            map.setTileAt(i, j, brickType);
        }
    for (auto i = 1; i < 14; i++) {
        for (auto j = 1; j < 14; j++) {
            map.setTileAt(i, j, floorType);
        }
    }
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
	
    
    


