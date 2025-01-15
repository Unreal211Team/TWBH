#pragma once

#include <memory>
#include <ctime>
#include <iostream>
#include <random>
#include "Monster.h"

using namespace std;
class ActingMonster
{
protected:
	Monster* monster;

public:
	ActingMonster() = default;
	ActingMonster(Monster& m) : monster(&m) {};
	void setMonster(Monster& monster);
	virtual void doAttack() = 0;
	virtual int getAttack() const = 0;
};