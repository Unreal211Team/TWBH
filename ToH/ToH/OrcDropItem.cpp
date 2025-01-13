#include "OrcDropItem.h"
#include "Character.h"

using namespace std;

OrcDropItem::OrcDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

std::string OrcDropItem::getName() const
{
	return name;
}

bool OrcDropItem::canUse() const
{
	return canUsing;
}

void OrcDropItem::use(Character* character) const
{	// ��밡���� �������� �ƴ�
	return;
}

int OrcDropItem::getPrice() const
{
	return price;
}