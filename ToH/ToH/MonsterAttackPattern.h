#pragma once
#include <random>
#include "Monster.h"

class MonsterAttackPattern
{
public:
	virtual bool doAttack(const Monster& monster) = 0;
	virtual int getDamage() = 0;
};