#include "Troll.h"
#include <random>
#include "TrollDropItem.h"
#include <algorithm>  // max() �Լ� ����� ���� �ʿ�

using namespace std;

Troll::Troll(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

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