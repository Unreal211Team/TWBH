#pragma once

#include "Monster.h"
#include "Character.h"
#include "Shop.h"



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


	// 수정사항
	void visitShop(Character* character, Shop* shop);
	int getValidatedInput(const string& prompt, int minValue, int maxValue);

};