#pragma once

#include "MonsterFactory.h"
#include "MonsterPatternFactory.h"

class ActingMonster
{
public:
	ActingMonster();

	void doAttack();

	string getName() const;
	int getHealth() const;
	int getDamage() const;
	void takeDamage(int damage);
	Item* dropItem() const;

	Monster& getMonster() { return *monster; };
private:
	int damage;
	shared_ptr<Monster> monster;
	MonsterPatternFactory monsterPattern;
};