#include "HealthPotion.h"
#include "Character.h"
#include <iostream>
#include <algorithm>  // min() 함수 사용을 위해 필요

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
	cout << "체력을 회복합니다." << endl;
	int HP = character->getHealth() + healthRestore;
	int maxHP = character->getMaxHealth();

	// 최대 체력을 초과하지 못함.
	HP = min(HP, maxHP);

	character->setHealth(HP);
}

int HealthPotion::getPrice() const
{
	return price;
}