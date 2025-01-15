#pragma once

#include "FindDiffWordMonster.h"
#include "ParryingMonster.h"

class AttackModeMonsterFactory
{
public:
	static AttackModeMonsterFactory& getInstance();
	shared_ptr<AttackModeMonster> getRandomMonster(Monster& monster);

private:
	vector<shared_ptr<AttackModeMonster>> monsters;

	AttackModeMonsterFactory();
	~AttackModeMonsterFactory() = default;

	AttackModeMonsterFactory(const AttackModeMonsterFactory&) = delete;
	AttackModeMonsterFactory& operator=(const AttackModeMonsterFactory&) = delete;
};