#include "ParryingMonster.h"

int ParryingMonster::getAttack() const
{
    return this->damage;
}

void ParryingMonster::doAttack()
{
    Character* character = Character::getInstance("");

    random_device rd;
    uniform_int_distribution<int> random(0, 25);
    string inputWord;

    char escapeChar = 'a' + random(rd);
    cout << endl << "������ ����! ȸ���Ͻ÷��� " << escapeChar << "�� �Է����ּ���" << endl;

    clock_t start = clock();
    cin >> inputWord;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    double timeOut = 1.0 + this->timeOutPlus - (static_cast<double>(character->getLevel()) * 0.1);

    if (spendTime < timeOut && inputWord.size() == 1 && inputWord[0] == escapeChar)
    {
        cout << "ȸ�� ����! ���� ���ݷ��� ����ȭ�ߴ�!" << endl;
        this->damage = 0;
    }
    else
    {
        cout << "ȸ�� ����!" << endl;
        this->damage = monster->getAttack();
    }
}
