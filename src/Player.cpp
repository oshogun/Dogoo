#include "Player.h"

Player::Player() : abilities(6)
{
}

void Player::setName (const std::string _name)
{
	name = _name;
}
std::string Player::getName()
{
	return name;
}
void Player::setHP (int hp)
{
	HP = hp;
}
void Player::setMP(int mp)
{
	MP = mp;
}
int Player::getHP()
{
	return HP;
}
int Player::getMP()
{
	return MP;
}
void Player::setRace(RACES _race)
{
	race = _race;
}
RACES Player::getRace()
{
	return race;
}
void Player::setPlayerStatus(PLAYER_STATUS _status)
{
	status = _status;
}
PLAYER_STATUS Player::getPlayerStatus()
{
	return status;
}
void Player::setStr(unsigned str)
{
	abilities[ABILITIES::STR] = str;
}
void Player::setDex(unsigned dex)
{
	abilities[ABILITIES::DEX] = dex;
}
void Player::setInt(unsigned intelligence)
{
	abilities[ABILITIES::INT] = intelligence;
} 
void Player::setWis(unsigned wis)
{
	abilities[ABILITIES::WIS] = wis;
}
void Player::setCha(unsigned cha)
{	
	abilities[ABILITIES::CHA] = cha;
}
unsigned Player::getStr()
{
	return abilities[ABILITIES::STR];
}
unsigned Player::getDex()
{
	return abilities[ABILITIES::DEX];
}
unsigned Player::getInt()
{
	return abilities[ABILITIES::INT];
}
unsigned Player::getWis()
{
	return abilities[ABILITIES::WIS];
}
unsigned Player::getCha()
{
	return abilities[ABILITIES::CHA];
}
void Player::setAge(int _age)
{
	age = _age;
}
int Player::getAge()
{
	return age;
}
unsigned Player::getLevel()
{
	return level;
}
void Player::setLevel(unsigned _level)
{
	level = _level;
}
void Player::levelUp()
{
	level++;
}

