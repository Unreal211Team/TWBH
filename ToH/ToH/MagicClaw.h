#pragma once
#include "Skill.h"
#include "Character.h"

class MagicClaw : public Skill
{
public:
    MagicClaw() : Skill("매직 클로", 60, 3.0) {}

    void use(Character* player, Character* target) override
    {
        if (player->getMana() < mana) {
            cout << "자원이 부족합니다!" << endl;
            return;
        }
        player->reduceMana(mana);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "가 매직 클로로 " << target->getName()
            << "에게 " << damage << " 데미지를 입혔습니다!" << endl;
    }
};