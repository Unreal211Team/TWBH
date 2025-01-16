#include "Troll.h"
#include <random>
#include "TrollDropItem.h"


Troll::Troll(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

	static int count = 1;

	name = "Troll";
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);

	asciiArt = R"(
      _.--'\   |   /'--._
    .'   '._.''.'.'_.-'  `.
   /   .-'         '-.    \
  /  .'               '.   \
 /   /                  \   \
 ;   ;   (o)     (o)    ;   ;
 |   |      _       _   |   |
 |   |     ( '-.-' )    |   |
 |   |      \_/ \_/     |   |
 ;   ;      _/   \_     ;   ;
  \   \    .'       `.  /  /
   `._/`. /           \ .'.'
      `..'             `..'
    )";

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

	cout << getName() << "을 공격합니다! ";
	cout << getName() << " 체력: " << getHealth() << endl;
}

Item* Troll::dropItem() const
{
	Item* drop = new TrollDropItem();
	return drop;
}