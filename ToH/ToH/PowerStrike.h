#pragma once
#include "Skill.h"
#include "Character.h"
#include "Report.h"

class PowerStrike : public Skill
{
private:

    string name;
    int skillCost;
    int multiplier;


public:
    PowerStrike()
        : name("PowerStrike")
        , skillCost(30)
        , multiplier(2)
    {}

    void use(Character* player, Monster* target) override
    {
        if (player->getMana() < skillCost)
        {
            cout << "마나가 부족합니다! \n";
            return;
        }
        player->reduceMana(skillCost);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "가 파워스트라이크로 " << target->getName()
            << "에게 " << damage << " 데미지를 입혔습니다!" << endl;
        REPORT->OnBattleEvent("파워스트라이크", "SkillAttack", damage);

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