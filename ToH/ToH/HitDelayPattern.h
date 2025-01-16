#pragma once

#include "MonsterAttackPattern.h"
class HitDelayPattern : public MonsterAttackPattern
{
public:
	HitDelayPattern() = default;


	// MonsterAttackPattern을(를) 통해 상속됨
	bool doAttack(const Monster& monster) override;

private:
	int damage = 0;


	// MonsterAttackPattern을(를) 통해 상속됨
	int getDamage() override;

};