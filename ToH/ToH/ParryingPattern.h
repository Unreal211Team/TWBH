#pragma once

#include "MonsterAttackPattern.h"
#include "Character.h"

class ParryingPattern : public MonsterAttackPattern
{
public:
	ParryingPattern() = default;

	// MonsterAttackPattern을(를) 통해 상속됨
	bool doAttack(const Monster& monster) override;
	int getDamage() override;
private:
	int damage = 0;

	const int timeOutPlus = 1;

};