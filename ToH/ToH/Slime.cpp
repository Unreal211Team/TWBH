#include "Slime.h"
#include <random>
#include "SlimeDropItem.h"
#include <algorithm>  // max() 함수 사용을 위해 필요


Slime::Slime(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

	static int count = 1;

	name = "Slime" + to_string(count++);
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);
}

string Slime::getName() const
{
	return name;
}

int Slime::getHealth() const
{
	return health;
}

int Slime::getAttack() const
{
	return attack;
}

void Slime::takeDamage(int damage)
{
	health = max(0, health - damage);
}

Item* Slime::dropItem() const
{
	Item* drop = new SlimeDropItem();
	return drop;
}