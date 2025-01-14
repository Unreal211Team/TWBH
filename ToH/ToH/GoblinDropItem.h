#pragma once

#include "Item.h"

class GoblinDropItem : public Item
{
private:
	const string name;
	const bool canUsing;	// 아이템 사용 가능 여부
	const int price;

public:
	GoblinDropItem(string name = "부서진 고블린의 창", bool canUsing = false, int price = 200);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};