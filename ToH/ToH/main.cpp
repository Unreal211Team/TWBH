#include <iostream>
#include "GameManager.h"
#include "Shop.h"
#include "BossMonster.h"
#include "Battle.h"
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

	while (character.getLevel() < 10 && character.getHealth() > 0)
	{

		// 배틀
		cout << "\n==================================================" << endl;

		Battle battle = Battle();
		battle.doBattle();
		if (character.getHealth() == 0)
		{
			break;
		}

		gameManager->visitShop(&character, shop);

	}

	if (character.getLevel() < 10)
	{
		return 0;
	}


	cout << "\n" << endl;

	// 레벨이 10이면 보스전, 추후에 main에서 분리 필요할지도?

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << "Warning! ";
		}
		cout << endl;
	}

	cout << "\n --- Boss 출현! ---\n" << endl;

	monster = new BossMonster();

	gameManager->battle(&character, monster);

	delete shop;
	delete gameManager;

	return 0;
}