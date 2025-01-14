#include "EliteDropItem.h"
#include "Character.h"

using namespace std;

EliteDropItem::EliteDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

std::string EliteDropItem::getName() const
{
	return name;
}

bool EliteDropItem::canUse() const
{
	return canUsing;
}

void EliteDropItem::use(Character* character) const
{	// ��밡���� �������� �ƴ�
	return;
}

int EliteDropItem::getPrice() const
{
	return price;
}