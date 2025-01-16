#include "FindDiffWordPattern.h"

bool FindDiffWordPattern::doAttack(const Monster& monster)
{
    Character& character = Character::getInstance();

    random_device rd;
    uniform_int_distribution<int> randomCol(0, Lstring.size() * 3);
    uniform_int_distribution<int> randomRow(1, character.getLevel());
    string str;
    string tempString{ Lstring };
    int changeRow = randomRow(rd);

    int answer = 0;
    cout << "\n==========================\n";
    cout << "��ƴ�� ã��!!" << endl << endl;

    for (int col = 0; col < character.getLevel(); col++)
    {
        int changeCol = randomCol(rd);
        string tempString(10, 'l');
        if (changeCol < Lstring.size())
        {
            tempString[changeCol] = 'i';
            answer++;
        }
        cout << tempString << endl;

    }

    cout << "i�� ������?" << endl;
    cout << "==========================\n\n";
    clock_t start = clock();
    cin >> str;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    if (spendTime < timeOut && to_string(answer) == str)
    {
        cout << "�� �� �� �� �� �� �� �� �� ��\n";
        cout << "��ƴ�� ���� ȸ���ߴ�!!" << endl;
        this->damage = 0;
        cout << "�� �� �� �� �� �� �� �� �� ��\n";
        return true;
    }
    else
    {
        cout << "--------------------------\n";
        cout << "��ƴ�� ã�����ߴ�" << endl;
        this->damage = monster.getAttack();
        cout << "--------------------------\n";
        return false;
    }

}

int FindDiffWordPattern::getDamage()
{
    return this->damage;
}



