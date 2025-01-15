#include "ActingMonster.h"



void ActingMonster::setMonster(Monster& monster)
{
    this->monster = &monster;
}

int ActingMonster::getAttack() const
{
    return this->monster->getAttack();
}

