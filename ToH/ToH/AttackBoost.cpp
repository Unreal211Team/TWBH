#include "AttackBoost.h"
#include "Character.h"
#include <iostream>


AttackBoost::AttackBoost(string name, bool canUsing, int price, int attackIncrease)
	: name(name), canUsing(canUsing), price(price), attackIncrease(attackIncrease)
{
}

string AttackBoost::getName() const
{
	return name;
}

bool AttackBoost::canUse() const
{
	return canUsing;
}

void AttackBoost::use(Character* character) const
{
	cout << "공격력이 상승합니다." << endl;
	int attack = character->getAttack() + attackIncrease;
	character->setAttack(attack);
}

int AttackBoost::getPrice() const
{
	return price;
}