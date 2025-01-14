#include "Orc.h"
#include <random>
#include "OrcDropItem.h"
#include <algorithm>  // max() �Լ� ����� ���� �ʿ�


Orc::Orc(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

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