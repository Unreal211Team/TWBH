#pragma once

#include "Monster.h"
#include "Character.h"

class GameManager
{
private:
	static GameManager* instance;

public:
	static GameManager* getInstance();
	Monster* generateMonster(int level);
	void battle(Character* player, Monster* monster);
	void displayInventory(Character* player);
	void useItemFromInventory(Character* player);
};