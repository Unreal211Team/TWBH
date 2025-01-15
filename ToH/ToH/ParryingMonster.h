#pragma once

#include "AttackModeMonster.h"

class ParryingMonster : public AttackModeMonster
{
public:
	ParryingMonster() = default;
	ParryingMonster(shared_ptr<Monster> monster) : AttackModeMonster(*monster) {};
	int getAttack() const;
	void doAttack() override;

private:
	int damage = 0;

	const int timeOut = 2;
};