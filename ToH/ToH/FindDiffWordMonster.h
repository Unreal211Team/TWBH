#pragma once

#include "ActingMonster.h"
#include "Character.h"

class FindDiffWordMonster : public ActingMonster
{
public:
	FindDiffWordMonster() = default;
	FindDiffWordMonster(Monster& monster) : ActingMonster(monster) {};
	int getAttack() const;
	void doAttack() override;

private:
	int damage = 0;
	string Lstring = string(10, 'l');
	const int timeOut = 5;
};