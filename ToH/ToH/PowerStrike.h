#pragma once
#include "Skill.h"
#include "Character.h"

class PowerStrike : public Skill
{
public:
    PowerStrike() : Skill("�Ŀ���Ʈ����ũ", 30, 1.5) {}

    void use(Character* player, Character* target) override
    {
        if (player->getResource() < mana)
        {
            cout << "�ڿ��� �����մϴ�!" << sendl;
            return;
        }
        player->reduceResource(cost);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "�� �Ŀ���Ʈ����ũ�� " << target->getName()
            << "���� " << damage << " �������� �������ϴ�!" << sendl;
    }
};