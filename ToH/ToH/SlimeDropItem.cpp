#include "SlimeDropItem.h"
#include "Character.h"


SlimeDropItem::SlimeDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

string SlimeDropItem::getName() const
{
	return name;
}

bool SlimeDropItem::canUse() const
{
	return canUsing;
}

void SlimeDropItem::use(Character* character) const
{	// 사용가능한 아이템이 아님
	return;
}

int SlimeDropItem::getPrice() const
{
	return price;
}