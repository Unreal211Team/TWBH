#include "AttackModeMonsterFactory.h"

AttackModeMonsterFactory& AttackModeMonsterFactory::getInstance()
{
    static AttackModeMonsterFactory attackModeMonsterFactory;
    return attackModeMonsterFactory;
    // TODO: ���⿡ return ���� �����մϴ�.
}

shared_ptr<ActingMonster> AttackModeMonsterFactory::getRandomMonster(Monster& monster)
{
    random_device rd;
    uniform_int_distribution<int> random(0, this->monsters.size() - 1);
    int randomMonsterIndex = random(rd);
    ActingMonster* randomMonster = monsters[randomMonsterIndex].get();
    randomMonster->setMonster(monster);

    return monsters[randomMonsterIndex];
}

AttackModeMonsterFactory::AttackModeMonsterFactory()
{
    this->monsters = {make_shared<FindDiffWordMonster>(), make_shared<ParryingMonster>()};
}
