#include "Slime.h"
#include <random>
#include "SlimeDropItem.h"


Slime::Slime(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

	static int count = 1;

	name = "Slime";
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);

	asciiArt = R"(
            _____
         .-'     `-.
       .'           `.
      /   O      O    \
     :                 :
   \  /     _______    \  /
       `.___________.'
 
    )";

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

	cout << getName() << "을 공격합니다! ";
	cout << getName() << " 체력: " << getHealth() << endl;
}

Item* Slime::dropItem() const
{
	Item* drop = new SlimeDropItem();
	return drop;
}