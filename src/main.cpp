#include <SFML/Graphics.hpp>
#include <string>
#include "ResourceHolder.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include "Map.h"


// TEMPORARY SHIT:
Map map(32,32);
Tile brickType(TileTypes::BRICK);
Tile floorType(TileTypes::FLOOR);
// Drawing a map for testing purposes

// TODO this is temporary and just for test:
// this entire file is temporary and just for test
void printMap() 
{
    for (auto i = 0; i < 32; i++) {

        for (auto j = 0; j < 32; j++) {
            std::cout << map.getTileAt(i,j).getCurrentAscii();
            if (j == 31) std::cout << "\n";
        }

    }
}
int main()
{   
    brickType.setAscii('#');
    floorType.setAscii('.');
    brickType.setOccupable(false);
    floorType.setOccupable(true);
    for (auto i = 0; i < 32; i++)
        for (auto j = 0; j < 32; j++) {
            map.setTileAt(i, j, brickType);
        }
    for (auto i = 1; i < 31; i++) {
        for (auto j = 1; j < 31; j++) {
            map.setTileAt(i, j, floorType);
        }
    }
    bool done = false;
    map.setPlayerPosition(15,15);
    map.getTileAt(10,10).setContainsObject(true);
    while(!done) {
        printMap();
        std::cout << "Command? ";
        std::string command;
        std::cin >> command;
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        if (command == "north") {
            map.movePlayer(Directions::NORTH);
        } else if (command == "south") {
            map.movePlayer(Directions::SOUTH);
        } else if (command == "east") {
            map.movePlayer(Directions::EAST);
        } else if (command == "west") {
            map.movePlayer(Directions::WEST);
        } else if (command == "exit") {
            done = true;
        } else {
            std::cout << "Invalid command\n";
        }
        std::cout << '\n';

    }

   
}
	
    
    


