#pragma once
#include <random>
#include "Monster.h"
#include "EliteMonster.h"

class Evolve {
private:
    random_device rd;
    default_random_engine generator;
    uniform_int_distribution<int> distribution;

public:
    //������ : ���� ���� ����
    Evolve()
        : generator(rd()), distribution(0, 100) {
    }

    // ���͸� ��ȭ��Ű�� �Լ�
    Monster* evolve(Monster* monster) {
        if (distribution(generator) < 30) { // 30% Ȯ��
            return new EliteMonster(monster);
        }
        else {
            return monster;
        }
    }
};

