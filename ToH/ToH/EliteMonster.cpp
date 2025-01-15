#include "EliteMonster.h"
#include "EliteDropItem.h"

/// <summary>
/// ������
/// ����Ʈȭ�� ���ʹ� ü�� ���ݷ� 2��
/// </summary>
/// <param name="monster"></param>
EliteMonster::EliteMonster(Monster* monster)
{
	originalMonster = monster;
	name = "Elite_" + monster->getName();
	health = monster->getHealth() * 2;
	attack = monster->getAttack() * 2;
}

//�̸�
string EliteMonster::getName() const
{
	return name;
}

//ü��
int EliteMonster::getHealth() const
{
	return health;
}

//����
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
