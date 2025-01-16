#include "ActingMonster.h"

ActingMonster::ActingMonster()
{
	MonsterFactory monsterFactory = MonsterFactory();
	this->monster = monsterFactory.makeMonster();
	this->damage = monster->getAttack();
	this->monsterPattern = MonsterPatternFactory();
}

void ActingMonster::doAttack()
{
	 if (this->monsterPattern.doRandomPatrens(*monster))
	 {
		 this->damage = 0;
	 }
	 else
	 {
		 this->damage = monster->getAttack();
	 }
}

string ActingMonster::getName() const
{
	return this->monster->getName();
}

int ActingMonster::getHealth() const
{
	return this->monster->getHealth();
}

int ActingMonster::getDamage() const
{
	return this->damage;
}

void ActingMonster::takeDamage(int damage)
{
	this->monster->takeDamage(damage);
}

Item* ActingMonster::dropItem() const
{
	return this->monster->dropItem();
}
