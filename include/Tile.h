#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"

enum TileTypes {
    BRICK,
    FLOOR,  
    // TODO add more types
};

class Tile {
public:
    Tile(){}
    Tile(TileTypes _type);
    void setSprite(const sf::Sprite & _sprite); 
    sf::Sprite & getSprite();
    const sf::Sprite & getSprite() const;
    TileTypes getType();
    const TileTypes getType() const;
    void setAscii(char _asciiCharacter);
    char getAscii();
    char getCurrentAscii();
    bool getContainsPlayer();
    void setContainsPlayer(bool _containsPlayer);
    bool getContainsObject();
    void setContainsObject(bool _containsObject);
    bool getContainsMonster();
    void setContainsMonster(bool _containsMonster);
    bool getOccupable();
    void setOccupable(bool _occupable);
private:
    sf::Sprite sprite;
    TileTypes type;
    char asciiCharacter; // the base ascii character of the tile
    char currentAscii; // to keep up the ascii in case it needs to be updated
    bool containsPlayer; // true if a player is currently on the tile
    bool containsObject; // true if item or chest currently on the tile
    bool containsMonster; // true if monster currently on the tile
    bool occupable; // can this tile be occupied by a player, monster or object
};

