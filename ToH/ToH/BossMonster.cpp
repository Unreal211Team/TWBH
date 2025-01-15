#include "BossMonster.h"
#include <random>
#include "BossMonsterDropItem.h"

using namespace std;

BossMonster::BossMonster(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(50, 60);
	uniform_int_distribution<int> randomAttack(5, 10);

	name = "Dragon";
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);
}

string BossMonster::getName() const
{
	return name;
}

int BossMonster::getHealth() const
{
	return health;
}

int BossMonster::getAttack() const
{
	return attack;
}

void BossMonster::takeDamage(int damage)
{
	health -= damage;
	health = health < 0 ? 0 : health;

	cout << getName() << "�� �����մϴ�! ";
	cout << getName() << " ü��: " << getHealth() << endl;
}

Item* BossMonster::dropItem() const
{
	Item* drop = new BossMonsterDropItem();
	return drop;
}