#pragma once
#include <vector>

#include "Goblin.h"
#include "Slime.h"
#include "Orc.h"
#include "Troll.h"
#include "BossMonster.h"
#include "EliteMonster.h"
#include "Character.h"
#include "Factory.h"
#include "Evolve.h"

class MonsterFactory : public Factory
{
public:
	MonsterFactory();
	shared_ptr<Monster> makeMonster();

private:
	shared_ptr<Monster> makeNomalMonster();
	shared_ptr<Monster> makeBossMonster();

	vector<shared_ptr<Monster>> monsters;
	vector<shared_ptr<Monster>> bossMonsters;
	int characterLevel;

};
