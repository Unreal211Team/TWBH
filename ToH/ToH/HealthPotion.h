#pragma once

#include "Item.h"

class HealthPotion : public Item
{
private:
	const string name;
	const bool canUsing;		// 아이템 사용 가능 여부
	const int price;
	const int healthRestore;	// 체력 회복량

public:
	HealthPotion(string name = "HealthPotion", bool canUsing = true, int price = 100, int healthRestore = 50);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};