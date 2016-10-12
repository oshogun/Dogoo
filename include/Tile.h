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
private:
    sf::Sprite sprite;
    TileTypes type;
};

