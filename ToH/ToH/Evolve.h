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
    //생성자 : 랜덤 난수 생성
    Evolve()
        : generator(rd()), distribution(0, 100) {
    }

    // 몬스터를 진화시키는 함수
    shared_ptr<Monster> evolve(shared_ptr<Monster>& monster) {
        if (distribution(generator) < 30) { // 30% 확률
            return make_shared<EliteMonster>(monster);
            cout << "ABFA";
        }
        else {
            return monster;
        }
    }
};

