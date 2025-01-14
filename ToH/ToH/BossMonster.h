#pragma once

#include "Monster.h"

class BossMonster : public Monster
{
private:
	string name;
	int health;
	int attack;

public:
	BossMonster(int level = 10);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
};