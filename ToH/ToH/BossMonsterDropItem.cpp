#include "BossMonsterDropItem.h"
#include "Character.h"
#include <iostream>


BossMonsterDropItem::BossMonsterDropItem(string name, bool canUsing, int price)
	: name(name), canUsing(canUsing), price(price)
{
}

string BossMonsterDropItem::getName() const
{
	return name;
}

bool BossMonsterDropItem::canUse() const
{
	return canUsing;
}

void BossMonsterDropItem::use(Character* character) const
{	
	cout << "�巡�� ��Ʈ�� �����մϴ�." << endl;
	cout << "ü���� 100�� ����մϴ�." << endl;
	cout << "���ݷ��� 100�� ����մϴ�." << endl;

	// ���� ���ݷ°� �ִ� ü�� ����
	character->setAttack(character->getAttack() * 100);
	character->setMaxHealth(character->getMaxHealth() * 100);
	// �� �Ŀ� ���� ü�� ������Ʈ
	character->setHealth(character->getMaxHealth());

	return;
}

int BossMonsterDropItem::getPrice() const
{
	return price;
}