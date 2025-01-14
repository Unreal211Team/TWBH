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
{	// ��밡���� �������� �ƴ�
	return;
}

int TrollDropItem::getPrice() const
{
	return price;
}