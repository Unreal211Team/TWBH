#pragma once

#include "ActingMonster.h"
class HitDelayMonster : public ActingMonster
{
public:
	HitDelayMonster() = default;


	// ActingMonster을(를) 통해 상속됨
	void doAttack() override;

	int getAttack() const override;

private:
	int damage = 0;
};