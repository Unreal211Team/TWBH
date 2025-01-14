#pragma once

#include "Item.h"

class OrcDropItem : public Item
{
private:
	const string name;
	const bool canUsing;
	const int price;

public:
	OrcDropItem(string name = "부서진 오크의 망치", bool canUsing = false, int price = 200);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};