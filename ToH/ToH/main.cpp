#include <iostream>
#include "GameManager.h"
#include "Shop.h"
#include "BossMonster.h"
#include "Battle.h"
#include "CharacterUI.h"
#include "Report.h"

using namespace std;

int main()
{
	
	GameManager* gameManager = GameManager::getInstance();
	Shop* shop = Shop::getInstance();
	
	string heroName = "";

	cout << "===========================\n";
	cout << "   ☆ ★ Game Start ★ ☆\n";
	cout << "===========================\n\n";
	cout << "캐릭터 이름을 입력하세요: ";

	// 이름 입력 받기
	cin >> heroName;

	Character& character = Character::getInstance();
	character.setName(heroName);
	Monster* monster = nullptr;
	system("cls");

	cout << "생성 완료! \n";
	
	character.displayStatus();

	string action = "";

	bool isDigit = false;	//입력값이 숫자인지 아닌지 판단할 때 쓰임
	int act = 0;

	while (character.getGold() < 20000 && character.getHealth() > 0)
	{

		// 배틀
		cout << "\n==================================================" << endl;

		Battle battle = Battle();
		battle.doBattle();

		// 사망
		if (character.getHealth() == 0)
		{
			break;
		}

		gameManager->visitShop(&character, shop);

	}

	if (character.getGold() >= 20000)
	{
		CharacterUI::displayEscape(character);
	}

	REPORT->GenerateReport();

	delete shop;
	delete gameManager;

	return 0;
}