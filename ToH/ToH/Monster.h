#pragma once

#include <string>
#include "Item.h"

class Monster
{
public:
	virtual std::string getName() const = 0;
	virtual int getHealth() const = 0;
	virtual	int getAttack() const = 0;
	virtual void takeDamage(int damage) = 0;
	virtual	Item* dropItem() const = 0;
};