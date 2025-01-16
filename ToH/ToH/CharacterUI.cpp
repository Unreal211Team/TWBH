#include "CharacterUI.h"
#include <iostream>

using namespace std;

void CharacterUI::displayStatus(const Character* character)
{
    cout << "\n --- status ---\n\n";
    cout << "�̸�: " << character->getName() << "\n";
    cout << "Lv." << character->getLevel() << "\n";
    cout << "Exp (" << character->getExperience() << "/" << character->getMaxExperience() << ")\n";
    cout << "HP (" << character->getHealth() << "/" << character->getMaxHealth() << ")\n";
    cout << "���ݷ� " << character->getAttack() << "\n";
    cout << " --- ----- ---\n\n";
}

void CharacterUI::displayExperienceGain(const Character* character, int experience)
{
    cout << character->getName() << "�� " << experience << " Exp�� ȹ���Ͽ����ϴ�.\n";
}

void CharacterUI::displayGoldGain(const Character* character, int gold)
{
    if (gold > 0)
        cout << character->getName() << "�� " << gold << " ��带 ȹ���߽��ϴ�.\n";
    else
        cout << character->getName() << "�� " << (-gold) << " ��带 �Ҹ��߽��ϴ�.\n";
}

void CharacterUI::displayDamageTaken(const Character* character, int damage)
{
    cout << character->getName() << "��(��) �����մϴ�! ";
    cout << character->getName() << " ü��: " << character->getHealth() << endl;
}

void CharacterUI::displayLevelUp(const Character* character)
{
    cout << character->getName() << "��(��) ������! Lv." << character->getLevel() << endl;
}

void CharacterUI::displayItemGain(const Character* character, const string& itemName)
{
    cout << character->getName() << "�� \"" << itemName << "\"�� ȹ���߽��ϴ�.\n";
}

void CharacterUI::displayItemUse(const Character* character, const string& itemName)
{
    cout << itemName << "�� ����մϴ�.\n";
}

void CharacterUI::displayItemCannotUse()
{
    cout << "��� �Ұ����� �������Դϴ�.\n";
}

void CharacterUI::displayDeath(const Character* character)
{
    cout << character->getName() << "��(��) ����߽��ϴ�. ���� ����!\n";
}
