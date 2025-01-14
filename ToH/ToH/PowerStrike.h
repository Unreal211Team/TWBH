#pragma once
#include "Skill.h"
#include "Character.h"

class PowerStrike : public Skill
{
public:
    PowerStrike() : Skill("파워스트라이크", 30, 1.5) {}

    void use(Character* player, Character* target) override
    {
        if (player->getResource() < mana)
        {
            cout << "자원이 부족합니다!" << sendl;
            return;
        }
        player->reduceResource(cost);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "가 파워스트라이크로 " << target->getName()
            << "에게 " << damage << " 데미지를 입혔습니다!" << sendl;
    }
};