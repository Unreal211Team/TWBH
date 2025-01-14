#pragma once

#include "Monster.h"

class Goblin : public Monster
{
private:
	string name;
	int health;
	int attack;

public:
	Goblin(int level = 0);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
};