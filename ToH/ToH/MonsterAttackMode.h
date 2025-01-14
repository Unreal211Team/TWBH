#pragma once

#include <memory>
#include <ctime>
#include <iostream>
#include <random>
#include "Monster.h"

using namespace std;
class MonsterAttackMode : public Monster
{
protected:
	shared_ptr<Monster> monster;
public:
	MonsterAttackMode(shared_ptr<Monster> m) : monster(m) {};
	int getAttack() const override;
	string getName() const override;
	int getHealth() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
};