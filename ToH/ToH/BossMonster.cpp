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

	asciiArt = R"(
          __        _
       _/  \    _(\(o
      /     \  /  _  ^^^o
     /   !   \/  ! '!!!v'
    !  !  \ _' ( \____
    ! . \ _!\   \===^\)
     \ \_!  / __!
      \!   /    \
(\_      _/   _\ )
 \ ^^--^^ __-^ /(__
  ^^----^^    "^--v'
    )";

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

	cout << getName() << "을 공격합니다! ";
	cout << getName() << " 체력: " << getHealth() << endl;
}

Item* BossMonster::dropItem() const
{
	Item* drop = new BossMonsterDropItem();
	return drop;
}