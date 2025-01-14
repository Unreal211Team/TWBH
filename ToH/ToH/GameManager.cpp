#include "GameManager.h"
#include "Item.h"
#include "iostream"
#include <random>
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"


GameManager* GameManager::instance = nullptr;

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new GameManager();
	}

	return instance;
}

Monster* GameManager::generateMonster(int level)
{
	random_device rd;
	uniform_int_distribution<int> random(1, 4);

	int randomMonster = random(rd);

	Monster* monster = nullptr;

	switch (randomMonster)
	{
	case 1:
		monster = new Goblin(level);
		break;

	case 2:
		monster = new Orc(level);
		break;

	case 3:
		monster = new Troll(level);
		break;

	case 4:
		monster = new Slime(level);
		break;

	default:
		break;
	}

	return monster;
}

void GameManager::battle(Character* player, Monster* monster)
{
	int experience = 50;// ���� ���� ����ġ 50
	int itemDrop = 30;	// ������ ��� Ȯ�� 30��

	random_device rd;
	uniform_int_distribution<int> randomG(10, 20);
	uniform_int_distribution<int> randomI(1, 100);

	int randomGold = randomG(rd);

	if (monster->getName() == "Dragon")
	{
		cout << "���� ";
	}

	cout << "���� " << monster->getName() << " ����! ";
	cout << "ü��: " << monster->getHealth();
	cout << ", ���ݷ�: " << monster->getAttack() << endl;
	
	string action = "";

	bool isDigit = false;	//�Է°��� �������� �ƴ��� �Ǵ��� �� ����
	int act = 0;

	while (true) {

		cout << "\n1)���� 2)�κ��丮 3)����â\n";
		cout << "�Է�: ";

		cin >> action;

		cout << endl;

		if (action != "1" && action != "2" && action != "3")
		{
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}

		// �Է� �� 2. �κ��丮 - ������ ���
		if (action == "2")
		{
			displayInventory(player);

			if (player->getInventory().size() == 0)
			{
				continue;
			}

			cout << "\n����)�ش� ������ ��� Q)������";
			cout << "�Է�: ";

			cin >> action;

			if (action == "Q" || action == "q")
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

			if (act > player->getInventory().size() || act <= 0)
			{
				cout << "�߸��� �Է��Դϴ�." << endl;
				continue;
			}

			player->useItem(act - 1);

			continue;
		}

		// �Է� �� 3. �������ͽ� ���
		if (action == "3")
		{
			player->displayStatus();
			continue;
		}

		/*
		* ������ - �Է� �� 1. ����
		* �÷��̾ ���� ����
		*/

		monster->takeDamage(player->getAttack());

		// ���Ͱ� �׾��� ��
		if (monster->getHealth() == 0)
		{
			cout << player->getName() << "�� ";
			cout << monster->getName() << "�� �����մϴ�! ";
			cout << monster->getName() << " óġ!" << endl;

			// ������ ����� ��
			if (monster->getName()=="Dragon")
			{
				Item* drop = monster->dropItem();
				cout << player->getName() << "�� \"";
				cout << drop->getName() << "\"�� ȹ���߽��ϴ�." << endl;
				player->addItem(drop);
				cout << "\n���� " << player->getName() << "�� ���� ������ ��ȭ�� ��������." << endl;
				break;
			}

			player->addExperience(experience);
			player->addGold(randomGold);
			
			cout << player->getName() << "�� ";
			cout << experience << " EXP�� ";
			cout << randomGold << " ��带 ȹ���߽��ϴ�." << endl;

			if (randomI(rd) <= 30)
			{
				Item* drop = monster->dropItem();
				cout << player->getName() << "�� \"";
				cout << drop->getName() << "\"�� ȹ���߽��ϴ�." << endl;
				player->addItem(drop);
			}

			// ĳ���� ������
			if (player->IsLevelUp())
			{
				player->levelUp();
				cout << player->getName() << "�� ������! ";
				cout << "Lv." << player->getLevel() << endl;
			}

			cout << "\nHP: " << player->getHealth() << "/" << player->getMaxHealth();
			cout << "  EXP: " << player->getExperience() << "/" << player->getMaxExperience();
			cout << "  ���: " << player->getGold() << "��" << endl;

			break;
		}

		cout << player->getName() << "�� ";
		cout << monster->getName() << "�� �����մϴ�! ";
		cout << monster->getName() << " ü��: " << monster->getHealth() << endl;


		/*
		* ���Ͱ� �÷��̾� ����
		*/
		
		player->takeDamage(monster->getAttack());

		cout << monster->getName() << "�� ";
		cout << player->getName() << "�� �����մϴ�! ";
		cout << player->getName() << " ü��: " << player->getHealth() << endl;

		// �÷��̾ �׾��� ��
		if (player->getHealth() == 0)
		{
			cout << player->getName() << "�� ����߽��ϴ�. ���� ����!" << endl;
			break;
		}
	}

	delete monster;

	monster = nullptr;
}

void GameManager::displayInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	cout << " --- Inventory ---" << endl;

	if (inventory.empty())
	{
		cout << " ����\n" << endl;
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << ". " << inventory[i]->getName() << " " << inventory[i]->getPrice() << "��" << endl;
	}

	cout << endl;
}