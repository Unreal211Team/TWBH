#include "MonsterParrying.h"

int MonsterParraying::getAttack() const
{
    random_device rd;
    uniform_int_distribution<int> random(0, 25);
    string inputWord;

    char escapeChar = 'a' + random(rd);
    cout << endl << "몬스터의 공격! 회피하시려면 " << escapeChar << "를 입력해주세요" << endl;

    clock_t start = clock();
    cin >> inputWord;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    if (spendTime < this->timeOut && inputWord.size() == 1 && inputWord[0] == escapeChar)
    {
        cout << "회피 성공! 적의 공격력을 무력화했다!" << endl;
        return 0;
    }

    cout << "회피 실패!" << endl;
    while (cin.fail())
    {
        cout << "잘못된값 다시입력하세요" << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return monster->getAttack();
}
