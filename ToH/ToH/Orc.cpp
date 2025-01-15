#include "Orc.h"
#include <random>
#include "OrcDropItem.h"


Orc::Orc(int level)
{
	random_device rd;
	uniform_int_distribution<int> randomHealth(20, 30);	// ü�� ���� ����
	uniform_int_distribution<int> randomAttack(5, 10);	// ���ݷ� ���� ����

	static int count = 1;

	name = "Orc" + to_string(count++);
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

	cout << getName() << "�� �����մϴ�! ";
	cout << getName() << " ü��: " << getHealth() << endl;
}

Item* Orc::dropItem() const
{
	Item* drop = new OrcDropItem();
	return drop;
}