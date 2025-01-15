#pragma once

#include "AttackModeMonster.h"
#include "Character.h"

class FindDiffWordMonster : public AttackModeMonster
{
public:
	FindDiffWordMonster() = default;
	FindDiffWordMonster(Monster& monster) : AttackModeMonster(monster) {};
	int getAttack() const;
	void doAttack() override;

private:
	int damage = 0;
	string Lstring = string(10, 'l');
	const int timeOut = 5;
};