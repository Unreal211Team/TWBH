#pragma once

#include "Item.h"

class EliteDropItem : public Item
{
private:
	const std::string name;
	const bool canUsing;
	const int price;

public:
	EliteDropItem(std::string name = "엘리트 몬스터의 코어", bool canUsing = false, int price = 500);
	std::string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};

