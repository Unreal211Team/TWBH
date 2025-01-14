#include "MonsterParrying.h"

int MonsterParraying::getAttack() const
{
    random_device rd;
    uniform_int_distribution<int> random(0, 25);
    string inputWord;

    char escapeChar = 'a' + random(rd);
    cout << endl << "������ ����! ȸ���Ͻ÷��� " << escapeChar << "�� �Է����ּ���" << endl;

    clock_t start = clock();
    cin >> inputWord;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    if (spendTime < this->timeOut && inputWord.size() == 1 && inputWord[0] == escapeChar)
    {
        cout << "ȸ�� ����! ���� ���ݷ��� ����ȭ�ߴ�!" << endl;
        return 0;
    }

    cout << "ȸ�� ����!" << endl;
    while (cin.fail())
    {
        cout << "�߸��Ȱ� �ٽ��Է��ϼ���" << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return monster->getAttack();
}
