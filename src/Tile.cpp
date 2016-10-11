#include "Tile.h"

Tile::Tile(TileTypes _type)
{
    type = _type;    
}

void Tile::setSprite(const sf::Sprite & _sprite)
{
    sprite = _sprite;
}

sf::Sprite & Tile::getSprite() 
{
    return sprite;
}

const sf::Sprite & Tile::getSprite() const
{
    return sprite;
}

TileTypes Tile::getType() 
{
    return type;
}


const TileTypes Tile::getType() const
{
    return type;
}
