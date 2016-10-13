#pragma once // TODO if necessary, replace with header guard. pragma once seems to be working fine with G++
#include <vector>
#include <string>

/*
*
*	The entire basis of this system is the classic D20 system, used in games such as Dungeons and Dragons. 
* 	The choice of said system it's because it's licensed under the Open Game License, 
*	it's easy to implement and has been popular between RPG players.
* 	All the reference I used for the system can be found in http://www.d20srd.org/
*/

enum ABILITIES {
	STR, // Strength
	DEX, // Dexterity
	CON, // Constitution
	INT, // Intelligence
	WIS, // Wisdom
	CHA, // Charisma
};

enum RACES {
	HUMAN,
	DWARF,
	ELF,
	GNOME,
	HALF_ELF,
	HALF_ORC,
	HALFLING,
};

enum PLAYER_STATUS {
	STABLE,
	DISABLED,
	DYING,
	DEAD,
};

class Player {
public:
	Player();
	~Player(){}
	void setName (const std::string _name);
	std::string getName();
	void setHP (int hp);
	void setMP (int mp);
	int getHP();
	int getMP();
	void setRace(RACES _race);
	RACES getRace();
	void setPlayerStatus(PLAYER_STATUS _status);
	PLAYER_STATUS getPlayerStatus();
	void setStr(unsigned str);
	void setDex(unsigned dex);
	void setInt(unsigned intelligence); // because "int" is a reserved word, duh
	void setWis(unsigned wis);
	void setCha(unsigned cha);
	unsigned getStr();
	unsigned getDex();
	unsigned getInt();
	unsigned getWis();
	unsigned getCha();
	void setAge(int _age);
	int getAge();
	unsigned getLevel();
	void setLevel(unsigned _level);
	void levelUp();

private:
	std::string name; // The player's name
	int HP, MP; // Health, mana
	int age;
	RACES race;
	PLAYER_STATUS status;
	unsigned level; 
	std::vector<unsigned> abilities;

		
};