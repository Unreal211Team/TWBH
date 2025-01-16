#pragma once

#include "MonsterAttackPattern.h"
class HitDelayPattern : public MonsterAttackPattern
{
public:
	HitDelayPattern() = default;


	// MonsterAttackPattern��(��) ���� ��ӵ�
	bool doAttack(const Monster& monster) override;

private:
	int damage = 0;


	// MonsterAttackPattern��(��) ���� ��ӵ�
	int getDamage() override;

};