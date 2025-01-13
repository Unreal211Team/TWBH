#pragma once

#include "Item.h"

class TrollDropItem : public Item
{
private:
	const std::string name;
	const bool canUsing;
	const int price;

public:
	TrollDropItem(std::string name = "�μ��� Ʈ���� ������", bool canUsing = false, int price = 200);
	std::string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};