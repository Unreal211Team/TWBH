#pragma once

#include <string>
#include <vector>
class Item;

class Character
{
private:
	static Character* instance;
	const std::string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int maxExperience;
	int gold;
	std::vector<Item*> inventory;
};