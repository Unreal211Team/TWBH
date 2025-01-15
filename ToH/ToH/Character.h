#pragma once

#include <string>
#include <vector>
#include "Monster.h"
#include "Skill.h"
#include <algorithm>

class Item;

using namespace std;

class Character
{
	// 
private:
	static Character* instance;


	Character(string name);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;


public:

	static Character* getInstance(const string& name = "");
	~Character();


private:

	// 
	const string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int maxExperience;
	int gold;
	int stamina;
	int mana;
	int maxMana;
	vector<Item*> inventory;
	vector<Skill*> skills;


	// 
	bool bIsAlive;

public:

	// Getter & Setter
	string getName() const;
	int getLevel() const;
	void setLevel(int level);
	int getHealth() const;
	void setHealth(int health);
	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);
	int getAttack() const;
	void setAttack(int attack);
	int getExperience() const;
	void setExperience(int experience);
	int getMaxExperience() const;
	void setMaxExperience(int maxExperience);
	int getGold() const;
	int getMana() const;
	int getMaxMana() const { return maxMana; }
	vector<Item*>& getInventory();
	const vector<Skill*>& getSkills() const { return skills; }

	// 

	bool isDead();
	void displayStatus() const;
	void addExperience(int experience);
	void addGold(int gold);
	void takeDamage(int damage);
	bool IsLevelUp() const;
	void levelUp();
	void addItem(Item* item);
	void useItem(int index);
	void reduceMana(int amount) { mana -= amount; }
	void recoverMana(int amount) { mana = min(mana + amount, maxMana); }


};