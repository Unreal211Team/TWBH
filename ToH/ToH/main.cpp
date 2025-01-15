#include <iostream>
#include "GameManager.h"
#include "Shop.h"
#include "BossMonster.h"

using namespace std;

int main()
{
	GameManager* gameManager = GameManager::getInstance();
	Shop* shop = Shop::getInstance();
	
	string heroName = "";

	cout << "   �١� Game Start �ڡ�\n";
	cout << "==================================================\n" << endl;
	cout << "ĳ���� �̸��� �Է��ϼ���: ";

	// �̸� �Է� �ޱ�
	cin >> heroName;

	Character* character = Character::getInstance(heroName);
	Monster* monster = nullptr;
	
	system("cls");

	cout << "���� �Ϸ�! \n";

	character->displayStatus();

	string action = "";

	bool isDigit = false;	//�Է°��� �������� �ƴ��� �Ǵ��� �� ����
	int act = 0;

	while (character->getLevel() < 10 && character->getHealth() > 0)
	{

		// ��Ʋ
		cout << "\n==================================================" << endl;
		monster = gameManager->generateMonster(character->getLevel());
		
		// ����
		gameManager->battle(character, monster);

		// ���
		if (character->getHealth() == 0)
		{
			break;
		}


		// ����
		cout << "\n==================================================\n" << endl;	// ���� ���� ������ main���� �и��� �ʿ� ������?
		cout << "������ �湮�Ͻðڽ��ϱ�?" << endl;
		cout << "Y)�Ѵ� �׿�)���Ѵ�: ";
		cin >> action;


		if (action.compare("y") == 0 || action.compare("Y") == 0)
		{
			while (true)
			{
				cout << "\n���: " << character->getGold() << endl;
				cout << "1)��� 2)�ȱ� 3)�׺� Q)������: ";
				cin >> action;

				if (action.compare("Q") == 0 || action.compare("q") == 0)
				{
					break;
				}

				// ����. ������ ���
				if (action.compare("1") == 0)
				{
					cout << endl;
					shop->displayItems();
					cout << "���� ��ȣ Q)���ư���: ";
					cin >> action;

					if (action.compare("Q") == 0 || action.compare("q") == 0)
					{
						continue;
					}

					// �Է� ���� �������� �Ǻ�
					isDigit = true;

					for (char actionChar : action)
					{
						if (!isdigit(actionChar))
						{
							isDigit = false;
							break;
						}
					}

					// �Է� ���� ���ڰ� �ƴ϶��
					if (!isDigit)
					{
						cout << "�߸��� �Է��Դϴ�." << endl;
						continue;
					}

					act = stoi(action);

					if (act <= 0 || act > 2)	// shop���� �Ǹ��ϴ� ������ ������ 2����. �ϵ� �ڵ� ���� �ʿ�**
					{
						cout << "�߸��� �Է��Դϴ�." << endl;
						continue;
					}

					shop->buyItem(act - 1, character);
					cout << endl;
				}

				// ����. ������ �ȱ�
				else if (action.compare("2") == 0)
				{
					cout << endl;
					gameManager->displayInventory(character);

					if (character->getInventory().size() == 0)
					{
						cout << "�Ǹ� ������ �������� �����ϴ�." << endl;
						continue;
					}

					cout << "������ 60% �������� �Ǹ��մϴ�." << endl;

					cout << "�Ǹ� ��ȣ Q)���ư���: ";
					cin >> action;

					if (action.compare("Q") == 0 || action.compare("q") == 0)
					{
						continue;
					}

					// �Է� ���� �������� �Ǻ�
					isDigit = true;

					for (char actionChar : action)
					{
						if (!isdigit(actionChar))
						{
							isDigit = false;
							break;
						}
					}

					// �Է� ���� ���ڰ� �ƴ϶��
					if (!isDigit)
					{
						cout << "�߸��� �Է��Դϴ�.1" << endl;
						continue;
					}

					act = stoi(action);

					if (act > character->getInventory().size() || act <= 0)
					{
						cout << "�߸��� �Է��Դϴ�.2" << endl;
						continue;
					}

					shop->sellItem(act - 1, character);
					cout << endl;
				}

				// ����. �׺�
				else if (action.compare("3") == 0)
				{
					shop->playGamble(character);
				}

				else // 1, 2, 3, Q �ܿ� �ٸ� �� �Է�
				{
					cout << "�߸��� �Է��Դϴ�." << endl;
				}
			}
		}
	}

	if (character->getLevel() < 10)
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

	gameManager->battle(character, monster);

	delete shop;
	delete character;
	delete gameManager;

	return 0;
}