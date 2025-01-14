#pragma once

#include "Item.h"

class GoblinDropItem : public Item
{
private:
	const string name;
	const bool canUsing;	// ������ ��� ���� ����
	const int price;

public:
	GoblinDropItem(string name = "�μ��� ����� â", bool canUsing = false, int price = 200);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};