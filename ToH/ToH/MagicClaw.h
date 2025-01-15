#pragma once
#include "Skill.h"
#include "Character.h"

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
            cout << "������ �����մϴ�!" << endl;
            return;
        }
        player->reduceMana(skillCost);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "�� ���� Ŭ�η� " << target->getName()
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