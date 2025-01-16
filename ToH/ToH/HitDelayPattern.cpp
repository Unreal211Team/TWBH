#include "HitDelayPattern.h"

bool HitDelayPattern::doAttack(const Monster& monster)
{
    random_device rd;
    uniform_int_distribution<int> random(3, 5);
    string str;
    int goalTime = random(rd);
    cout << "���� �����Ϸ��Ѵ�! " << goalTime << "�Ŀ� ������!" << endl;
    cout << "==========================\n";
    cout << "�غ� �Ǿ����� �ƹ�Ű�� ��������!" << endl;
    cout << "==========================\n\n";
    cin >> str;
    clock_t start = clock();
    cout << "��ǥ �ð��̶�� �ƹ�Ű�� ��������!" << endl;
    cin >> str;
    clock_t end = clock();
    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    int ceilTime = static_cast<int>(ceil(spendTime + 0.5));
    cout << ceilTime << "�� �Ŀ� �����̽��ϴ�" << endl;
    if (ceilTime == goalTime)
    {
        cout << "�� �� �� �� �� �� �� �� �� ��\n";
        cout << "ȸ�� �����߽��ϴ�!" << endl;
        cout << "�� �� �� �� �� �� �� �� �� ��\n";
        this->damage = 0;
        return true;
    }
    else
    {
        cout << "--------------------------\n";
        cout << "�����߽��ϴ�!" << endl;
        cout << "--------------------------\n";
        this->damage = monster.getAttack();
        return false;
    }
    

}

int HitDelayPattern::getDamage()
{
    return this->damage;
}
