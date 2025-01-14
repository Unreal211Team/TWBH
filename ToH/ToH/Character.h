#pragma once

#include <string>
#include <vector>
#include "Skill.h"
class Item;

using namespace std;

class Character
{
private:
	static Character* instance;
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



	Character(string name);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

public:
	static Character* getInstance(const string& name = "");
	void displayStatus() const;
	string getName() const;
	int getLevel() const;
	int getHealth() const;
	void setHealth(int health);
	int getMaxHealth() const;
	void setMaxHealth(int maxHealth);
	int getAttack() const;
	void setAttack(int attack);
	int getExperience() const;
	int getMaxExperience() const;
	void addExperience(int experience);
	int getGold() const;
	void addGold(int gold);
	void takeDamage(int damage);
	vector<Item*>& getInventory();
	bool IsLevelUp() const;
	void levelUp();
	void addItem(Item* item);
	void useItem(int index);
	int getMana() const { return mana; }
	int getMaxMana() const { return maxMana; }
	void reduceMana(int amount) { mana -= amount; }
	void recoverMana(int amount) { mana = min(mana + amount, maxMana); }

	Character() : mana(100), maxMana(100)
	{
		skills.push_back(new PowerStrike());
		skills.push_back(new MagicClaw());
	}

	~Character() {
		for (Skill* skill : skills)
			delete skill;
	}

	const vector<Skill*>& getSkills() const { return skills; }

	~Character();
};