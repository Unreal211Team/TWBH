#include "Troll.h"
#include <random>
#include "TrollDropItem.h"
#include <algorithm>  // max() 함수 사용을 위해 필요

using namespace std;

Troll::Troll(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

	static int count = 1;

	name = "Troll" + to_string(count++);
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);
}

string Troll::getName() const
{
	return name;
}

int Troll::getHealth() const
{
	return health;
}

int Troll::getAttack() const
{
	return attack;
}

void Troll::takeDamage(int damage)
{
	health = max(0, health - damage);
}

Item* Troll::dropItem() const
{
	Item* drop = new TrollDropItem();
	return drop;
}