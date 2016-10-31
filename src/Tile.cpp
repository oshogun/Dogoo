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

void Tile::setAscii(char _asciiCharacter) {
	asciiCharacter = _asciiCharacter;
}

char Tile::getAscii() {
	return asciiCharacter;
}

bool Tile::getContainsPlayer() {
	return containsPlayer;
}

void Tile::setContainsPlayer(bool _containsPlayer) {
	containsPlayer = _containsPlayer;
	if (containsPlayer)
		setAscii('@');
}

bool Tile::getContainsObject() {
	return containsObject;
}

void Tile::setContainsObject(bool _containsObject) {
	containsObject = _containsObject;
	if (containsObject)
		setAscii('O');
}

bool Tile::getContainsMonster() {
	return containsMonster;
	if (containsMonster)
		setAscii('M');
}

void Tile::setContainsMonster(bool _containsMonster) {
	containsMonster = _containsMonster;
}