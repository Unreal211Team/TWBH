#include "BossMonsterDropItem.h"
#include "Character.h"
#include <iostream>


BossMonsterDropItem::BossMonsterDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

string BossMonsterDropItem::getName() const
{
	return name;
}

bool BossMonsterDropItem::canUse() const
{
	return canUsing;
}

void BossMonsterDropItem::use(Character* character) const
{	

	return;
}

int BossMonsterDropItem::getPrice() const
{
	return price;
}