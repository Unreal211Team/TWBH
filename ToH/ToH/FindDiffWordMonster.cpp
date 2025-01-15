#include "FindDiffWordMonster.h"
using namespace std;
int FindDiffWordMonster::getAttack() const
{
    return this->damage;
}

void FindDiffWordMonster::doAttack()
{
    Character* character = Character::getInstance("");

    random_device rd;
    uniform_int_distribution<int> randomCol(0, Lstring.size() * 3);
    uniform_int_distribution<int> randomRow(1, character->getLevel());
    string str;
    string tempString{ Lstring };
    int changeRow = randomRow(rd);
    
    int answer = 0;

    cout << "ºóÆ´À» Ã£ÀÚ!!" << endl << endl;

    for (int col = 0; col < character->getLevel(); col++)
    {
        int changeCol = randomCol(rd);
        string tempString(10, 'l'); 
        if (changeCol < Lstring.size())
        {
            tempString[changeCol] = 'i';
            answer++;
        }
        cout << tempString <<endl;

    }

    cout << "iÀÇ °¹¼ö´Â?" << endl;
    clock_t start = clock();
    cin >> str;
    clock_t end = clock();

    double spendTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    if (spendTime < timeOut && to_string(answer) == str)
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
