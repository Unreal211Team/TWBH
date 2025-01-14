#pragma once

#include "Item.h"

class HealthPotion : public Item
{
private:
	const string name;
	const bool canUsing;		// ������ ��� ���� ����
	const int price;
	const int healthRestore;	// ü�� ȸ����

public:
	HealthPotion(string name = "HealthPotion", bool canUsing = true, int price = 50, int healthRestore = 50);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};