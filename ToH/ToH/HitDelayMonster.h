#pragma once

#include "ActingMonster.h"
class HitDelayMonster : public ActingMonster
{
public:
	HitDelayMonster() = default;


	// ActingMonster��(��) ���� ��ӵ�
	void doAttack() override;

	int getAttack() const override;

private:
	int damage = 0;
};