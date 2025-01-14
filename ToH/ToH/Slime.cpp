#include "Slime.h"
#include <random>
#include "SlimeDropItem.h"
#include <algorithm>  // max() �Լ� ����� ���� �ʿ�


Slime::Slime(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

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