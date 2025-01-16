#include "MonsterPatternFactory.h"

MonsterPatternFactory::MonsterPatternFactory()
{
	this->patterns = { make_shared<FindDiffWordPattern>(), make_shared<ParryingPattern>(), make_shared<HitDelayPattern>() };
}

const int MonsterPatternFactory::getPatternSize() const
{
	return this->patterns.size();
}

bool MonsterPatternFactory::doPatrens(int index, Monster& monster)
{
	if (index < this->patterns.size())
	{
		return this->patterns[index]->doAttack(monster);
	}
}

bool MonsterPatternFactory::doRandomPatrens(Monster& monster)
{
	
	return this->patterns[makeRandomInt(0, this->patterns.size() - 1)]->doAttack(monster);
}

