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

	while (character.getLevel() < 10 && character.getHealth() > 0)
	{

		// ��Ʋ
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

	// ������ 10�̸� ������, ���Ŀ� main���� �и� �ʿ�������?

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << "Warning! ";
		}
		cout << endl;
	}

	cout << "\n --- Boss ����! ---\n" << endl;

	monster = new BossMonster();

	gameManager->battle(&character, monster);

	delete shop;
	delete gameManager;

	return 0;
}