#include "GameManager.h"
#include "Item.h"
#include <iostream>
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
	cout << ", ���ݷ�: " << monster->getAttack() << "\n";


	// ���� ����
	while (true)
	{
		// ���� ���� ���� (������ ü���� 0���� ũ��.)
		if (monster->getHealth() <= 0)
		{
			break;
		}


		int choiceAction;

		cout << "1. ����   2. �κ��丮   3. ����â \n";
		cout << "�Է� : ";

		while (true) 
		{
			cin >> choiceAction;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "�߸� �Էµ� ���Դϴ�.\n";
				cout << "�ٽ� �Է����ּ���. :";
			}
			else
			{
				break;
			}
		}

		

		switch (choiceAction)
		{

			// 1. ���� ���� 
		case 1:
		{



			// �÷��̾��� ����
			cout << player->getName() << "��(��) ";
			monster->takeDamage(player->getAttack());

			// �÷��̾��� ���ݿ� ���Ͱ� �׾��� ��
			if (monster->getHealth() == 0)
			{
				cout << monster->getName() << " óġ!" << endl;


				// ������ �����ϴ� ����
				player->addExperience(experience);
				player->addGold(randomGold);

				if (randomI(rd) <= itemDrop)
				{
					Item* drop = monster->dropItem();
					player->addItem(drop);
				}

				// ĳ���� ������ Ȯ���ϴ� ����
				if (player->IsLevelUp())
				{
					player->levelUp();
				}

				// ���� ���Ͱ� �������� Ȯ���ϴ� ����
				if (monster->getName() == "Dragon")
				{
					cout << "\n���� " << player->getName() << "�� ���� ������ ��ȭ�� ��������." << endl;
					break;
				}
				return;
			}


			// ������ ����
			cout << monster->getName() << "��(��) ";
			player->takeDamage(monster->getAttack());

			// ������ ���ݿ� �÷��̾ ����ߴ��� Ȯ���ϴ� ����
			if (player->getHealth() == 0)
			{
				player->isDead();
				return;
			}
			break;
		}

		// 2. �κ��丮 ����
		case 2:
		{
			displayInventory(player);
			useItemFromInventory(player);
			break;
		}


		// 3. ����â ����
		case 3:
		{
			player->displayStatus();
			break;
		}
		default:
		{
			cout << "�߸��� �Է°��Դϴ�. \n";
			break;
		}

		// ������ ������ ���� ��ü�� ����
		delete monster;
		monster = nullptr;
		}
	}
}



void GameManager::displayInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	cout << " --- Inventory ---" << endl;

	cout << " ������� : " << player->getGold() << " gold\n";

	if (inventory.empty())
	{
		cout << " ���� ������ : ����\n" << endl;
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << ". " << inventory[i]->getName() << " ( " << inventory[i]->getPrice() << " gold ) \n";
	}


	
}

void GameManager::useItemFromInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	int itemIndex;

	cout << "��ȣ�� �Է��Ͽ� ������ ����� �����մϴ�. \n";

	while (true)
	{
		cout << "0. �κ��丮 �ݱ� \n";
		cin >> itemIndex;

		if (itemIndex > 0 && itemIndex <= inventory.size())
		{
			player->useItem(itemIndex - 1);
			break;
		}
		else if (itemIndex == 0)
		{
			cout << "�κ��丮�� �ݽ��ϴ�. \n";
			break;
		}
		else
		{
			cout << "�߸��� �Է°��Դϴ�. \n";
		}
	}
}
