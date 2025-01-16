#include "MonsterFactory.h"

MonsterFactory::MonsterFactory()
{
    Character& character = Character::getInstance();
    int characterLevel = character.getLevel();
    this->monsters = { make_shared<Orc>(characterLevel), make_shared<Goblin>(characterLevel),make_shared<Slime>(characterLevel) ,make_shared<Troll>(characterLevel) };
    this->bossMonsters = { make_shared<BossMonster>(characterLevel) };
}

shared_ptr<Monster> MonsterFactory::makeMonster()
{
    int characterLevel = Character::getInstance().getLevel();
    if (characterLevel < 10)
    {
        return move(makeNomalMonster());
    }
    else
    {
        return move(makeBossMonster());
    };
}

shared_ptr<Monster> MonsterFactory::makeNomalMonster()
{

    return move(this->monsters[makeRandomInt(0, static_cast<int>(this->monsters.size() - 1))]);
}

shared_ptr<Monster> MonsterFactory::makeBossMonster()
{
    return move(this->bossMonsters[makeRandomInt(0, static_cast<int>(this->bossMonsters.size() - 1))]);
}


