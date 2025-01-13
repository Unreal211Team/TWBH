#pragma once

#include "Monster.h"

class Slime : public Monster
{
private:
	std::string name;
	int health;
	int attack;

public:
	Slime(int level = 0);
	std::string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
};