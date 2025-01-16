#pragma once

#include "Item.h"

class AttackBoost : public Item
{
private:
	const string name;
	const bool canUsing;		// ������ ��� ���� ����
	const int price;
	const int attackIncrease;	// ���ݷ� ������

public:
	AttackBoost(string name = "AttackBoost", bool canUsing = true, int price = 100, int attackIncrease = 10);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};