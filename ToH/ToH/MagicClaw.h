#pragma once
#include "Skill.h"
#include "Character.h"
#include "Report.h"

class MagicClaw : public Skill
{
public:

    string name;
    int skillCost;
    int multiplier;

public:
    MagicClaw()
        : name("MagicClaw")
        , skillCost(60)
        , multiplier(3)
    {}

    void use(Character* player, Monster* target) override
    {
        if (player->getMana() < skillCost) {
            cout << "마나가 부족합니다!" << endl;
            return;
        }
        player->reduceMana(skillCost);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "가 매직 클로로 " << target->getName()
            << "에게 " << damage << " 데미지를 입혔습니다!" << endl;
        REPORT->OnBattleEvent("매직클로", "SkillAttack", damage);
    }

    const string& getName() const
    {
        return name;
    }
    int getMana() const
    {
        return skillCost;
    }
};