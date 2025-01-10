#include "Orc.h"
#include <random>
#include <iostream>

Orc::Orc(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);
	uniform_int_distribution<int> randomAttack(5, 10);

	static int count = 1;

	name = "orc" + to_string(count++);
	health = level * randomHealth(rd);

	attack = level * randomAttack(rd);

	cout << name << endl;
	cout << health << endl;
	cout << attack << endl;
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
	health -= damage;
	health = health < 0 ? 0 : health;
}
