#include "Tile.h"

Tile::Tile(TileTypes _type)
{
    type = _type;
    occupable = false; 
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
	currentAscii = asciiCharacter;
}

char Tile::getAscii() {
	return asciiCharacter;
}
char Tile::getCurrentAscii() {
	return currentAscii;
}

bool Tile::getContainsPlayer() {
	return containsPlayer;
}

void Tile::setContainsPlayer(bool _containsPlayer) {
	containsPlayer = _containsPlayer;
	if (containsPlayer)
		currentAscii = '@';
	else {
		currentAscii = asciiCharacter;
	} 

}


bool Tile::getContainsObject() {
	return containsObject;
}

void Tile::setContainsObject(bool _containsObject) {
	containsObject = _containsObject;
	if (containsObject) {
		currentAscii = 'O';
		occupable = false;
	} else {
		currentAscii = asciiCharacter;
		occupable = true;
	}
}

bool Tile::getContainsMonster() {
	return containsMonster;
}

void Tile::setContainsMonster(bool _containsMonster) {
	containsMonster = _containsMonster;
	if (containsMonster)
		currentAscii = 'M';
	else
		currentAscii = asciiCharacter;
}

bool Tile::getOccupable() {
	return occupable;
}
void Tile::setOccupable(bool _occupable) {
	occupable = _occupable;
}