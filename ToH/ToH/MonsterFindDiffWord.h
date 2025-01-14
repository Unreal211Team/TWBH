#pragma once

#include "MonsterAttackMode.h"

class MonsterFindDiffWord : public MonsterAttackMode
{
public:
	MonsterFindDiffWord(shared_ptr<Monster> monster) : MonsterAttackMode(monster) {};

	int getAttack() const override;

private:
	string Lstring = string(10, 'l');
	const int timeOut = 5;
};