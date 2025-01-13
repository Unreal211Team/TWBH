#pragma once

#include "Item.h"

class SlimeDropItem : public Item
{
private:
	const std::string name;
	const bool canUsing;
	const int price;

public:
	SlimeDropItem(std::string name = "�������� �������� ����", bool canUsing = false, int price = 200);
	std::string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};