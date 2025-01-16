#include "EliteMonster.h"
#include "EliteDropItem.h"

/// <summary>
/// 생성자
/// 엘리트화된 몬스터는 체력 공격력 2배
/// </summary>
/// <param name="monster"></param>
EliteMonster::EliteMonster(Monster* monster)
{
	originalMonster = monster;
	name = "Elite_" + monster->getName();
	health = monster->getHealth() * 2;
	attack = monster->getAttack() * 2;
}

EliteMonster::EliteMonster(shared_ptr<Monster>& monster)
{
	this->originalMonster = monster.get();
	name = "Elite_" + monster->getName();
	health = monster->getHealth() * 2;
	attack = monster->getAttack() * 2;
	stringstream ss;
	ss << "\n\n           _/\\_/\\_" << endl;
	ss << "          /       \\" << endl;
	ss << "         /  Elite  \\" << endl;
	ss << "          \\_______/" << endl;

	asciiArt = ss.str() + originalMonster->getAsciiArt();
}

//이름
string EliteMonster::getName() const
{
	return name;
}

//체력
int EliteMonster::getHealth() const
{
	return health;
}

//공격
int EliteMonster::getAttack() const
{
	return attack;
}

//
void EliteMonster::takeDamage(int damage)
{
	health = max(0, health - damage);
}

//
Item* EliteMonster::dropItem() const
{
	Item* drop = new EliteDropItem();
	return drop;
}
