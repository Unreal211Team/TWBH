#pragma once

#include "Monster.h"

class Orc : public Monster
{
private:
	string name;
	int health;
	int attack;

public:
	Orc(int level = 0);
	string	getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
};