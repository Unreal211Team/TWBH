#pragma once

#include "Item.h"

class BossMonsterDropItem : public Item
{
private:
	const std::string name;
	const bool canUsing;
	const int price;

public:
	BossMonsterDropItem(std::string name = "�巡�� ��Ʈ", bool canUsing = true, int price = 10000000);
	std::string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};