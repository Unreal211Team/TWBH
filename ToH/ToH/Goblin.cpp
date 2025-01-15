#include "Goblin.h"
#include <random>
#include "GoblinDropItem.h"


Goblin::Goblin(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

	static int count = 1;

	name = "Goblin";
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);

	asciiArt = R"(
       ,      ,
      /(.-""-.)\
  |\  |  ,   ,  |  /|
   \\ |   O O   | //
    \\|     ^    |//
     -\    '    /-
      --.___.--
    )";

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

	cout << getName() << "�� �����մϴ�! ";
	cout << getName() << " ü��: " << getHealth() << endl;
}

Item* Goblin::dropItem() const
{
	Item* drop = new GoblinDropItem();
	return drop;
}