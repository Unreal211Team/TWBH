#include "ParryingPattern.h"

bool ParryingPattern::doAttack(const Monster& monster)
{
    Character& character = Character::getInstance();

    random_device rd;
    uniform_int_distribution<int> random(0, 25);
    string inputWord;

    char escapeChar = 'a' + random(rd);
    cout << "\n==========================\n";
    cout << "������ ����! ȸ���Ͻ÷��� " << escapeChar << "�� �Է����ּ���" << endl;
    cout << "==========================\n\n";

    clock_t start = clock();
    cin >> inputWord;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    double timeOut = 1.0 + this->timeOutPlus - (static_cast<double>(character.getLevel()) * 0.1);

    if (spendTime < timeOut && inputWord.size() == 1 && inputWord[0] == escapeChar)
    {
        cout << "\n�� �� �� �� �� �� �� �� �� ��\n\n";
        cout << "ȸ�� ����! ���� ���ݷ��� ����ȭ�ߴ�!" << endl;
        this->damage = 0;
        cout << "\n�� �� �� �� �� �� �� �� �� ��\n\n";
        return true;
    }
    else
    {
        cout << "\n--------------------------\n\n";
        cout << "ȸ�� ����!" << endl;
        this->damage = monster.getAttack();
        cout << "\n--------------------------\n\n";
        return false;
    }
   
}

int ParryingPattern::getDamage()
{
    return this->damage;
}
