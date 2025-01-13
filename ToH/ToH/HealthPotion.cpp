#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
#include <algorithm>  // min() �Լ� ����� ���� �ʿ�

using namespace std;

HealthPotion::HealthPotion(string name, bool canUsing, int price, int healthRestore)
	: name(name), canUsing(canUsing), price(price), healthRestore(healthRestore)
{
}

string HealthPotion::getName() const
{
	return name;
}

bool HealthPotion::canUse() const
{
	return canUsing;
}

void HealthPotion::use(Character* character) const
{
	cout << "ü���� ȸ���մϴ�." << endl;
	int HP = character->getHealth() + healthRestore;
	int maxHP = character->getMaxHealth();

	// �ִ� ü���� �ʰ����� ����.
	HP = min(HP, maxHP);

	character->setHealth(HP);
}

int HealthPotion::getPrice() const
{
	return price;
}