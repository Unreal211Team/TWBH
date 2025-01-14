#pragma once

#include "Item.h"

class SlimeDropItem : public Item
{
private:
	const string name;
	const bool canUsing;
	const int price;

public:
	SlimeDropItem(string name = "�������� �������� ����", bool canUsing = false, int price = 200);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};