#include <iostream>
#include "GameManager.h"
#include "Shop.h"
#include "BossMonster.h"
#include "Battle.h"
#include "CharacterUI.h"
using namespace std;

int main()
{
	GameManager* gameManager = GameManager::getInstance();
	Shop* shop = Shop::getInstance();
	
	string heroName = "";

	cout << "===========================\n";
	cout << "   �� �� Game Start �� ��\n";
	cout << "===========================\n\n";
	cout << "ĳ���� �̸��� �Է��ϼ���: ";

	// �̸� �Է� �ޱ�
	cin >> heroName;

	Character& character = Character::getInstance();
	character.setName(heroName);
	Monster* monster = nullptr;
	system("cls");

	cout << "���� �Ϸ�! \n";
	
	character.displayStatus();

	string action = "";

	bool isDigit = false;	//�Է°��� �������� �ƴ��� �Ǵ��� �� ����
	int act = 0;

	while (character.getGold() < 20000 && character.getHealth() > 0)
	{

		// ��Ʋ
		cout << "\n==================================================" << endl;

		Battle battle = Battle();
		battle.doBattle();

		// ���
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

	delete shop;
	delete gameManager;

	return 0;
}