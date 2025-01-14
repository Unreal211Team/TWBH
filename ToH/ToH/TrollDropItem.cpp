#include "TrollDropItem.h"
#include "Character.h"


TrollDropItem::TrollDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

string TrollDropItem::getName() const
{
	return name;
}

bool TrollDropItem::canUse() const
{
	return canUsing;
}

void TrollDropItem::use(Character* character) const
{	// 사용가능한 아이템이 아님
	return;
}

int TrollDropItem::getPrice() const
{
	return price;
}