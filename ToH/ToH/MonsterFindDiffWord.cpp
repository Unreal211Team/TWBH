#include "MonsterFindDiffWord.h"

int MonsterFindDiffWord::getAttack() const
{
    random_device rd;
    uniform_int_distribution<int> random(0, Lstring.size() - 1);
    string str;
    string tempString{ Lstring };
    int changePos = random(rd);
    tempString[changePos] = 'i';
    cout << "��ƴ�� ã��!!" << endl;
    cout << tempString << endl;
    cout << "i�� ��ġ��?" << endl;
    clock_t start = clock();
    cin >> str;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    if (spendTime < timeOut && to_string(changePos + 1) == str)
    {
        cout << "��ƴ�� ���� ȸ���ߴ�!!" << endl;
        return 0;
    }
    cout << "��ƴ�� ã�����ߴ�" << endl;
    return monster->getAttack();
}
