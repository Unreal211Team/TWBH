#include "Orc.h"
#include <random>
#include "OrcDropItem.h"


Orc::Orc(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// 체력 랜덤 범위
	uniform_int_distribution<int> randomAttack(5, 10);	// 공격력 랜덤 범위

	static int count = 1;

	name = "Orc";
	health = level * randomHealth(rd);
	attack = level * randomAttack(rd);

	asciiArt = R"(
      __,='`````'=/__
     '//  (o) \(o) \\`  
    //|     ,_)   (`\\
  // |  \_.-==-._.-  | \\
 //  |               |  \\
//   \    \       /   /  \\
//     '._  '.___' _.'    \\
/         `'-----'         
    )";

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

	cout << getName() << "을 공격합니다! ";
	cout << getName() << " 체력: " << getHealth() << endl;
}

Item* Orc::dropItem() const
{
	Item* drop = new OrcDropItem();
	return drop;
}