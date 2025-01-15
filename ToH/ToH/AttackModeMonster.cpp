#include "AttackModeMonster.h"



void AttackModeMonster::setMonster(Monster& monster)
{
    this->monster = &monster;
}

int AttackModeMonster::getAttack() const
{
    return this->monster->getAttack();
}

