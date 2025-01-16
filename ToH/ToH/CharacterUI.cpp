#include "CharacterUI.h"
#include <iostream>

using namespace std;

void CharacterUI::displayStatus(const Character* character)
{
    cout << "\n --- status ---\n\n";
    cout << "이름: " << character->getName() << "\n";
    cout << "Lv." << character->getLevel() << "\n";
    cout << "Exp (" << character->getExperience() << "/" << character->getMaxExperience() << ")\n";
    cout << "HP (" << character->getHealth() << "/" << character->getMaxHealth() << ")\n";
    cout << "공격력 " << character->getAttack() << "\n";
    cout << " --- ----- ---\n\n";
}

void CharacterUI::displayExperienceGain(const Character* character, int experience)
{
    cout << character->getName() << "가 " << experience << " Exp를 획득하였습니다.\n";
}

void CharacterUI::displayGoldGain(const Character* character, int gold)
{
    if (gold > 0)
        cout << character->getName() << "가 " << gold << " 골드를 획득했습니다.\n";
    else
        cout << character->getName() << "가 " << (-gold) << " 골드를 소모했습니다.\n";
}

void CharacterUI::displayDamageTaken(const Character* character, int damage)
{
    cout << character->getName() << "을(를) 공격합니다! ";
    cout << character->getName() << " 체력: " << character->getHealth() << endl;
}

void CharacterUI::displayLevelUp(const Character* character)
{
    cout << character->getName() << "이(가) 레벨업! Lv." << character->getLevel() << endl;
}

void CharacterUI::displayItemGain(const Character* character, const string& itemName)
{
    cout << character->getName() << "가 \"" << itemName << "\"을 획득했습니다.\n";
}

void CharacterUI::displayItemUse(const Character* character, const string& itemName)
{
    cout << itemName << "을 사용합니다.\n";
}

void CharacterUI::displayItemCannotUse()
{
    cout << "사용 불가능한 아이템입니다.\n";
}

void CharacterUI::displayDeath(const Character* character)
{
    cout << character->getName() << "이(가) 사망했습니다. 게임 오버!\n";
}

//탈출 메세지
void CharacterUI::displayEscape(const Character& character)
{
    cout << "골드를 모아 탈출에 성공하였습니다!\n";
}
