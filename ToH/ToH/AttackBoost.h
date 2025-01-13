#pragma once

#include "Item.h"

class AttackBoost : public Item
{
private:
	const std::string name;
	const bool canUsing;		// ������ ��� ���� ����
	const int price;
	const int attackIncrease;	// ���ݷ� ������

public:
	AttackBoost(std::string name = "AttackBoost", bool canUsing = true, int price = 50, int attackIncrease = 10);
	std::string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};