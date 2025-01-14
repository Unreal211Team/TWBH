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
	cout << "드래곤 하트를 복용합니다." << endl;
	cout << "체력이 100배 상승합니다." << endl;
	cout << "공격력이 100배 상승합니다." << endl;

	// 먼저 공격력과 최대 체력 증가
	character->setAttack(character->getAttack() * 100);
	character->setMaxHealth(character->getMaxHealth() * 100);
	// 그 후에 현재 체력 업데이트
	character->setHealth(character->getMaxHealth());

	return;
}

int BossMonsterDropItem::getPrice() const
{
	return price;
}