#pragma once

#include "Item.h"

class ManaPotion : public Item
{
private:
	const string name;
	const bool canUsing;		// ������ ��� ���� ����
	const int price;
	const int ManaRestore;	// ���� ȸ����

public:
	ManaPotion(string name = "ManaPotion", bool canUsing = true, int price = 50, int ManaRestore = 50);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};