#include "ManaPotion.h"
#include "Character.h"
#include "Report.h"
#include <iostream>
#include <algorithm>  // min() �Լ� ����� ���� �ʿ�


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
	cout << "������ ȸ���մϴ�." << endl;
	int MP = character->getMana() + ManaRestore;
	int maxMP = character->getMaxMana();

	// �ִ� ������ �ʰ����� ����.
	MP = min(MP, maxMP);

	REPORT->OnItemEvent("ManaPotion", "use", 0, ManaRestore);
	character->setMana(MP);
}

int ManaPotion::getPrice() const
{
	return price;
}