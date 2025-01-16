#include "Goblin.h"
#include <random>
#include "GoblinDropItem.h"


Goblin::Goblin(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

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

	cout << getName() << "을 공격합니다! ";
	cout << getName() << " 체력: " << getHealth() << endl;
}

Item* Goblin::dropItem() const
{
	Item* drop = new GoblinDropItem();
	return drop;
}