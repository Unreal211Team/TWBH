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
	BuffManager* manager = BuffManager::getInstance();		//버프 매니저
	if (manager->dupliBuffCheck(buffname))
	{
		manager->addBuff(name, 3);	//이름, 지속 턴
		return;						//중복시 안에서 턴만 늘려준다.
	}else{
		manager->addBuff(name, 3);	//없을경우 둘 다 입력
	}
	
	cout << "공격력이 상승합니다." << endl;
	int attack = character->getAttack() + attackIncrease;
	character->setAttack(attack);
	REPORT->OnItemEvent("AttackBoost", "use");
}

int AttackBoost::getPrice() const
{
	return price;
}