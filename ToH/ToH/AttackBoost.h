#pragma once

#include "Item.h"

class AttackBoost : public Item
{
private:
	const std::string name;
	const bool canUsing;		// 아이템 사용 가능 여부
	const int price;
	const int attackIncrease;	// 공격력 증가량

public:
	AttackBoost(std::string name = "AttackBoost", bool canUsing = true, int price = 50, int attackIncrease = 10);
	std::string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};