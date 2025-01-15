#include "Troll.h"
#include <random>
#include "TrollDropItem.h"


Troll::Troll(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

	static int count = 1;

	name = "Troll";
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

	cout << getName() << "�� �����մϴ�! ";
	cout << getName() << " ü��: " << getHealth() << endl;
}

Item* Troll::dropItem() const
{
	Item* drop = new TrollDropItem();
	return drop;
}