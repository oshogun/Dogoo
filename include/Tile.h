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
    void setSprite(const sf::Sprite & _sprite); // vou passar por cópia, sla
    sf::Sprite & getSprite();
    const sf::Sprite & getSprite() const;
    TileTypes getType();
    const TileTypes getType() const;
    void setAscii(char _asciiCharacter);
    char getAscii();
    bool getContainsPlayer();
    void setContainsPlayer(bool _containsPlayer);
    bool getContainsObject();
    void setContainsObject(bool _containsObject);
    bool getContainsMonster();
    void setContainsMonster(bool _containsMonster);
private:
    sf::Sprite sprite;
    TileTypes type;
    char asciiCharacter; // for CLI representation
    bool containsPlayer; // true if a player is currently on the tile
    bool containsObject; // true if item or chest currently on the tile
    bool containsMonster; // true if monster currently on the tile

};

