#pragma once

#include "FindDiffWordMonster.h"
#include "ParryingMonster.h"

class AttackModeMonsterFactory
{
public:
	static AttackModeMonsterFactory& getInstance();
	shared_ptr<ActingMonster> getRandomMonster(Monster& monster);

private:
	vector<shared_ptr<ActingMonster>> monsters;

	AttackModeMonsterFactory();
	~AttackModeMonsterFactory() = default;

	AttackModeMonsterFactory(const AttackModeMonsterFactory&) = delete;
	AttackModeMonsterFactory& operator=(const AttackModeMonsterFactory&) = delete;
};