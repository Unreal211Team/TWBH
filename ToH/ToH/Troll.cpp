#include "Troll.h"
#include <random>

Troll::Troll(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);
	uniform_int_distribution<int> randomAttack(5, 10);

	static int count = 1;

	name = "troll" + to_string(count++);
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
	health -= damage;
	health = health < 0 ? 0 : health;
}
