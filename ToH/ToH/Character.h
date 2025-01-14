#pragma once

#include <string>
#include <vector>
#include "Monster.h"

class Item;

using namespace std;

class Character
{
	// 싱글톤 영역
private:
	static Character* instance;


	Character(string name);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;


public:

	static Character* getInstance(const string& name = "");
	~Character();


private:

	// 멤버 변수
	const string name;
	int level;
	int health;
	int maxHealth;
	int attack;
	int experience;
	int maxExperience;
	int gold;
	vector<Item*> inventory;

	// 죽었는지 살아있는지
	bool bIsAlive;

public:

	// Getter & Setter
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
	int getGold() const;
	vector<Item*>& getInventory();


	// 기능
	void displayStatus() const;
	void addExperience(int experience);
	void addGold(int gold);
	void takeDamage(int damage);
	bool IsLevelUp() const;
	void levelUp();
	void addItem(Item* item);
	void useItem(int index);
	bool isDead();

};