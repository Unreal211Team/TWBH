#include "Goblin.h"
#include <random>
#include "GoblinDropItem.h"
#include <algorithm>  // max() �Լ� ����� ���� �ʿ�

using namespace std;

Goblin::Goblin(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

	static int count = 1;

	name = "Goblin" + to_string(count++);
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);
}

string Goblin::getName() const
{
	return name;
}

int Goblin::getHealth() const
{
	return health;
}

int Goblin::getAttack() const
{
	return attack;
}

void Goblin::takeDamage(int damage)
{
	health = max(0, health - damage);
}

Item* Goblin::dropItem() const
{
	Item* drop = new GoblinDropItem();
	return drop;
}