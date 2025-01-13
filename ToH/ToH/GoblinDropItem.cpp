#include "GoblinDropItem.h"
#include "Character.h"

using namespace std;

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
{	// ��밡���� �������� �ƴ�
	return;
}

int GoblinDropItem::getPrice() const
{
	return price;
}