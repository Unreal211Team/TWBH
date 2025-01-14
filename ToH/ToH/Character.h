#pragma once

#include <string>
#include <vector>
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
	vector<Item*> inventory;

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
	~Character();
};