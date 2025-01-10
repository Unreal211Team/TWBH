#include "Slime.h"
#include <random>

Slime::Slime(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);
	uniform_int_distribution<int> randomAttack(5, 10);

	static int count = 1;

	name = "slime" + to_string(count++);
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
	health -= damage;
	health = health < 0 ? 0 : health;
}
