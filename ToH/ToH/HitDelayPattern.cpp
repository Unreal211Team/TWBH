#include "HitDelayPattern.h"

bool HitDelayPattern::doAttack(const Monster& monster)
{
    random_device rd;
    uniform_int_distribution<int> random(3, 5);
    string str;
    int goalTime = random(rd);
    cout << "적이 공격하려한다! " << goalTime << "후에 눌러라!" << endl;
    cout << "==========================\n";
    cout << "준비 되었으면 아무키나 누르세요!" << endl;
    cout << "==========================\n\n";
    cin >> str;
    clock_t start = clock();
    cout << "목표 시간이라면 아무키나 누르세요!" << endl;
    cin >> str;
    clock_t end = clock();
    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    int ceilTime = static_cast<int>(ceil(spendTime + 0.5));
    cout << ceilTime << "초 후에 누르셨습니다" << endl;
    if (ceilTime == goalTime)
    {
        cout << "☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★\n";
        cout << "회피 성공했습니다!" << endl;
        cout << "☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★\n";
        this->damage = 0;
        return true;
    }
    else
    {
        cout << "--------------------------\n";
        cout << "실패했습니다!" << endl;
        cout << "--------------------------\n";
        this->damage = monster.getAttack();
        return false;
    }
    

}

int HitDelayPattern::getDamage()
{
    return this->damage;
}
