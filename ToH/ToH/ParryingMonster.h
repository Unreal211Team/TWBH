#pragma once

#include "ActingMonster.h"
#include "Character.h"

class ParryingMonster : public ActingMonster
{
public:
	ParryingMonster() = default;
	ParryingMonster(shared_ptr<Monster> monster) : ActingMonster(*monster) {};
	int getAttack() const;
	void doAttack() override;

private:
	int damage = 0;

	const int timeOutPlus = 1;
};