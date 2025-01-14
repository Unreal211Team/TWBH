#include "GoblinDropItem.h"
#include "Character.h"


GoblinDropItem::GoblinDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

string GoblinDropItem::getName() const
{
	return name;
}

bool GoblinDropItem::canUse() const
{
	return canUsing;
}

void GoblinDropItem::use(Character* character) const
{	// 사용가능한 아이템이 아님
	return;
}

int GoblinDropItem::getPrice() const
{
	return price;
}