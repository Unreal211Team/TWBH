#pragma once
#include "Skill.h"
#include "Character.h"

class MagicClaw : public Skill
{
public:
    MagicClaw() : Skill("���� Ŭ��", 60, 3.0) {}

    void use(Character* player, Character* target) override
    {
        if (player->getMana() < mana) {
            cout << "�ڿ��� �����մϴ�!" << endl;
            return;
        }
        player->reduceMana(mana);
        int damage = player->getAttack() * multiplier;
        target->takeDamage(damage);

        cout << player->getName() << "�� ���� Ŭ�η� " << target->getName()
            << "���� " << damage << " �������� �������ϴ�!" << endl;
    }
};