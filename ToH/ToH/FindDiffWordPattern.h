#pragma once

#include "MonsterAttackPattern.h"
#include "Character.h"

class FindDiffWordPattern : public MonsterAttackPattern
{
public:
	FindDiffWordPattern() = default;

	// MonsterAttackPattern��(��) ���� ��ӵ�
	bool doAttack(const Monster& monster) override;
	int getDamage() override;
private:
	int damage = 0;
	string Lstring = string(10, 'l');
	const int timeOut = 5;

};