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

	Character(std::string name);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;

public:
	static Character* getInstance(const std::string& name = "");
	void displayStatus() const;
	std::string getName() const;
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
	std::vector<Item*>& getInventory();
	bool IsLevelUp() const;
	void levelUp();
	void addItem(Item* item);
	void useItem(int index);
	~Character();
};