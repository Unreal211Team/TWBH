#include "FindDiffWordMonster.h"

int FindDiffWordMonster::getAttack() const
{
    return this->damage;
}

void FindDiffWordMonster::doAttack()
{
    Character* character = Character::getInstance("");

    random_device rd;
    uniform_int_distribution<int> random(0, Lstring.size() - 1);
    string str;
    string tempString{ Lstring };
    int changePos = random(rd);
    tempString[changePos] = 'i';
    cout << "ºóÆ´À» Ã£ÀÚ!!" << endl;
    cout << tempString << endl;
    cout << "iÀÇ À§Ä¡´Â?" << endl;
    clock_t start = clock();
    cin >> str;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    if (spendTime < timeOut && to_string(changePos + 1) == str)
    {
        cout << "ºóÆ´À» ÅëÇØ È¸ÇÇÇß´Ù!!" << endl;
        this->damage = 0;
    }
    else
    {
        cout << "ºóÆ´À» Ã£Áö¸øÇß´Ù" << endl;
        this->damage = monster->getAttack();
    }

}
