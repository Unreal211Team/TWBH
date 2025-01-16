#include "AttackBoost.h"
#include "Character.h"
#include "BuffManager.h"
#include "Report.h"
#include <iostream>


AttackBoost::AttackBoost(string name, bool canUsing, int price, int attackIncrease)
	: name(name), canUsing(canUsing), price(price), attackIncrease(attackIncrease)
{
}

string AttackBoost::getName() const
{
	return name;
}

bool AttackBoost::canUse() const
{
	return canUsing;
}

void AttackBoost::use(Character* character) const
{
	string buffname = name;
	BuffManager* manager = BuffManager::getInstance();		//���� �Ŵ���
	if (manager->dupliBuffCheck(buffname))
	{
		manager->addBuff(name, 3);	//�̸�, ���� ��
		return;						//�ߺ��� �ȿ��� �ϸ� �÷��ش�.
	}else{
		manager->addBuff(name, 3);	//������� �� �� �Է�
	}
	
	cout << "���ݷ��� ����մϴ�." << endl;
	int attack = character->getAttack() + attackIncrease;
	character->setAttack(attack);
	REPORT->OnItemEvent("AttackBoost", "use");
}

int AttackBoost::getPrice() const
{
	return price;
}