#include "MonsterAttackMode.h"



int MonsterAttackMode::getAttack() const
{
    return monster->getAttack();
}

string MonsterAttackMode::getName() const
{
    return monster->getName();
}

int MonsterAttackMode::getHealth() const
{
    return monster->getHealth();
}

void MonsterAttackMode::takeDamage(int damage)
{
    monster->takeDamage(damage);
}

Item* MonsterAttackMode::dropItem() const
{
    return monster->dropItem();
}
