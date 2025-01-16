#include "ManaPotion.h"
#include "Character.h"
#include "Report.h"
#include <iostream>
#include <algorithm>  // min() 함수 사용을 위해 필요


ManaPotion::ManaPotion(string name, bool canUsing, int price, int ManaRestore)
	: name(name), canUsing(canUsing), price(price), ManaRestore(ManaRestore)
{
}

string ManaPotion::getName() const
{
	return name;
}

bool ManaPotion::canUse() const
{
	return canUsing;
}

void ManaPotion::use(Character* character) const
{
	cout << "마나을 회복합니다." << endl;
	int MP = character->getMana() + ManaRestore;
	int maxMP = character->getMaxMana();

	// 최대 마나을 초과하지 못함.
	MP = min(MP, maxMP);

	REPORT->OnItemEvent("ManaPotion", "use", 0, ManaRestore);
	character->setMana(MP);
}

int ManaPotion::getPrice() const
{
	return price;
}