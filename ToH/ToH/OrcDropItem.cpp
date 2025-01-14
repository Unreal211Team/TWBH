#include "OrcDropItem.h"
#include "Character.h"


OrcDropItem::OrcDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

string OrcDropItem::getName() const
{
	return name;
}

bool OrcDropItem::canUse() const
{
	return canUsing;
}

void OrcDropItem::use(Character* character) const
{	// 사용가능한 아이템이 아님
	return;
}

int OrcDropItem::getPrice() const
{
	return price;
}