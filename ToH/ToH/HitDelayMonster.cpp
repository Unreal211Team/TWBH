#include "HitDelayMonster.h"

void HitDelayMonster::doAttack()
{
    random_device rd;
    uniform_int_distribution<int> random(3, 5);
    string str;
    int goalTime = random(rd);
    cout << "���� �����Ϸ��Ѵ�! " << goalTime << "�Ŀ� ������!" << endl;
    cout << "�غ� �Ǿ����� �ƹ�Ű�� ��������!" << endl;

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
        cout << "�����߽��ϴ�!" << endl;
        this->damage = 0;
    }
    else
    {
        cout << "�����߽��ϴ�!" << endl;
        this->damage = monster->getAttack();
    }

}

int HitDelayMonster::getAttack() const
{
    return this->damage;
}
