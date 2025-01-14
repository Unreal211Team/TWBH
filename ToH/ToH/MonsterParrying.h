#pragma once

#include "MonsterAttackMode.h"

class MonsterParraying : public MonsterAttackMode
{
public:
	MonsterParraying(shared_ptr<Monster> monster) : MonsterAttackMode(monster) {};

	int getAttack() const override;

private:
	int timeOut = 2;
};