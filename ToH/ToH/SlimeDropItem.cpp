#include "SlimeDropItem.h"
#include "Character.h"

using namespace std;

SlimeDropItem::SlimeDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

std::string SlimeDropItem::getName() const
{
	return name;
}

bool SlimeDropItem::canUse() const
{
	return canUsing;
}

void SlimeDropItem::use(Character* character) const
{	// ��밡���� �������� �ƴ�
	return;
}

int SlimeDropItem::getPrice() const
{
	return price;
}