#pragma once
#include "FindDiffWordPattern.h"
#include "HitDelayPattern.h"
#include "ParryingPattern.h"
#include "Factory.h"

class MonsterPatternFactory : public Factory
{
public:
	MonsterPatternFactory();
	bool doPatrens(int index, Monster& monster);
	bool doRandomPatrens(Monster& monster);
	const int getPatternSize() const;

private:
	vector<shared_ptr<MonsterAttackPattern>> patterns;
};