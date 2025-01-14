#include "Orc.h"
#include <random>
#include "OrcDropItem.h"
#include <algorithm>  // max() 함수 사용을 위해 필요


Orc::Orc(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

	static int count = 1;

	name = "Orc" + to_string(count++);
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);
}

string Orc::getName() const
{
	return name;
}

int Orc::getHealth() const
{
	return health;
}

int Orc::getAttack() const
{
	return attack;
}

void Orc::takeDamage(int damage)
{
	health = max(0, health - damage);
}

Item* Orc::dropItem() const
{
	Item* drop = new OrcDropItem();
	return drop;
}