#pragma once

#include "Item.h"

class BossMonsterDropItem : public Item
{
private:
	const string name;
	const bool canUsing;
	const int price;

public:
	BossMonsterDropItem(string name = "µå·¡°ï ÇÏÆ®", bool canUsing = false, int price = 1000);
	string getName() const override;
	bool canUse() const override;
	void use(Character* character) const override;
	int getPrice() const override;
};