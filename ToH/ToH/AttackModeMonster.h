#pragma once

#include <memory>
#include <ctime>
#include <iostream>
#include <random>
#include "Monster.h"

using namespace std;
class AttackModeMonster
{
protected:
	Monster* monster;

public:
	AttackModeMonster() = default;
	AttackModeMonster(Monster& m) : monster(&m) {};
	void setMonster(Monster& monster);
	virtual void doAttack() = 0;
	virtual int getAttack() const = 0;
};