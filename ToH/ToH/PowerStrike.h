#pragma once
#include "Skill.h"
#include "Character.h"

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
            cout << "������ �����մϴ�! \n";
            return;
        }
        player->reduceMana(skillCost);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "�� �Ŀ���Ʈ����ũ�� " << target->getName()
            << "���� " << damage << " �������� �������ϴ�!" << endl;
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