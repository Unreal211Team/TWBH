#include "ParryingPattern.h"

bool ParryingPattern::doAttack(const Monster& monster)
{
    Character& character = Character::getInstance();

    random_device rd;
    uniform_int_distribution<int> random(0, 25);
    string inputWord;

    char escapeChar = 'a' + random(rd);
    cout << "\n==========================\n";
    cout << "몬스터의 공격! 회피하시려면 " << escapeChar << "를 입력해주세요" << endl;
    cout << "==========================\n\n";

    clock_t start = clock();
    cin >> inputWord;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    double timeOut = 1.0 + this->timeOutPlus - (static_cast<double>(character.getLevel()) * 0.1);

    if (spendTime < timeOut && inputWord.size() == 1 && inputWord[0] == escapeChar)
    {
        cout << "\n☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★\n\n";
        cout << "회피 성공! 적의 공격력을 무력화했다!" << endl;
        this->damage = 0;
        cout << "\n☆ ★ ☆ ★ ☆ ★ ☆ ★ ☆ ★\n\n";
        return true;
    }
    else if (spendTime > timeOut)
    {
        cout << "\n--------------------------\n\n";
        cout << "회피에 늦었습니다!" << endl;
        this->damage = monster.getAttack();
        cout << "\n--------------------------\n\n";
        return false;
    }
    cout << "\n--------------------------\n\n";
    cout << "회피 입력 실패!" << endl;
    this->damage = monster.getAttack();
    cout << "\n--------------------------\n\n";
    return false;
    
   
}

int ParryingPattern::getDamage()
{
    return this->damage;
}
