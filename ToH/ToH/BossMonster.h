#pragma once

#include "Monster.h"

class BossMonster : public Monster
{
private:
	std::string name;
	int health;
	int attack;
};