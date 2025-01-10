#include "Goblin.h"
#include <random>

Goblin::Goblin(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);
	uniform_int_distribution<int> randomAttack(5, 10);

	static int count = 1;

	name = "goblin" + to_string(count++);
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
	health -= damage;
	health = health < 0 ? 0 : health;
}
