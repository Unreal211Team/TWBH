#include "GameManager.h"
#include "Item.h"
#include <iostream>
#include <random>
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "Evolve.h"
#include "BuffManager.h"
#include "Skill.h"
#include "AttackModeMonsterFactory.h"
#include "PowerStrike.h"
#include "MagicClaw.h"

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

	// ��ȭ : ���� Eliteȭ Ȯ�� 30%Ȯ��
	Evolve evolver;
	monster = evolver.evolve(monster);

	return monster;
}

void GameManager::battle(Character* player, Monster* monster)
{
	BuffManager* manager = BuffManager::getInstance();

	int experience = 50;// ���� ���� ����ġ 50
	int itemDrop = 30;	// ������ ��� Ȯ�� 30��

	random_device rd;
	uniform_int_distribution<int> randomG(10, 20);
	uniform_int_distribution<int> randomI(1, 100);

	int randomGold = randomG(rd);
	//�̸��� ���� ����޼��� ����
	if (monster->getName() == "Dragon")
	{
		cout << "�� �� �� �� �� ���� ";
		cout << "���� " << monster->getName() << " ����! �� �� �� �� �� " << endl;
		monster->displayArt();
	}
	else if (monster->getName().find("Elite") != string::npos) {	//find ��� ã�� ���ڰ� ������ npos��ȯ�ϹǷ� !=
		cout << "�� �� �� ����Ʈ ";
		cout << "���� " << monster->getName() << " ����! �� �� �� " << endl;
		monster->displayArt();
	}
	else {
		cout << "���� " << monster->getName() << " ����! " << endl;
		monster->displayArt();
	}

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

		cout << "1. ����   2. �κ��丮   3. ����â \n";

		int choiceAction = getValidatedInput("�Է����ּ��� :", 0, 3);

		switch (choiceAction)
		{

			// 1. ���� ���� 
		case 1:
		{
			int attackChoice;
			cout << "\n���� ����: " << player->getMana() << " / " << player->getMaxMana() << "\n";
			cout << "1. �Ϲݰ���  2. �Ŀ���Ʈ����ũ(30) 3. ����Ŭ��(60)\n";
			cout << "���� ���� : ";
			cin >> attackChoice;

			switch (attackChoice)
			{
			case 1:
				cout << player->getName() << "��(��) ";
				monster->takeDamage(player->getAttack());
				break;
			case 2:
			{
				PowerStrike powerStrike;
				powerStrike.use(player, monster);
				if (player->getMana() < powerStrike.getMana())
				{
					cout << "�ٸ� ������ �ϼ���.\n";
					continue;
				}
				break;
			}
			case 3:
			{
				MagicClaw magicClaw;
				magicClaw.use(player, monster);
				if (player->getMana() < magicClaw.getMana())
				{
					cout << "�ٸ� ������ �ϼ���.\n";
					continue;
				}
				break;
			}
			default:
				cout << "�߸��� �Է��Դϴ�.\n";
				continue;
			}

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

			AttackModeMonsterFactory& attackModeMonsterFactory = AttackModeMonsterFactory::getInstance();
			shared_ptr<ActingMonster> tempMonster = attackModeMonsterFactory.getRandomMonster(*monster);

			// ������ ����
			cout << monster->getName() << "��(��) ";
			player->takeDamage(tempMonster->getAttack());
			tempMonster->doAttack();

			cout << "�÷��̾��� ü�� :" << player->getHealth() << endl;
			// ������ ���ݿ� �÷��̾ ����ߴ��� Ȯ���ϴ� ����
			if (player->getHealth() == 0)
			{
				player->isDead();
				return;
			}

			cout << "\nHP: " << player->getHealth() << "/" << player->getMaxHealth();
			cout << "  EXP: " << player->getExperience() << "/" << player->getMaxExperience();
			cout << "  ���: " << player->getGold() << "��" << endl;

			if (manager->ActiveBuffsCheck())
			{
				manager->updateBuffs(player);
			}

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

		if (manager->ActiveBuffsCheck())
		{
			manager->updateBuffs(player);
		}

		// �÷��̾ �׾��� ��
		if (player->getHealth() == 0)
		{
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


void GameManager::visitShop(Character* character, Shop* shop)
{
	bool askVisitShop = true;

	while (askVisitShop)
	{
		cout << "\n==================================================\n" << endl;
		cout << "������ �湮�Ͻðڽ��ϱ�?" << endl;
		cout << "1. �Ѵ� \n";
		cout << "2. ���Ѵ�. \n";

		int choiceVisit = getValidatedInput("�Է����ּ��� :", 1, 2);

		switch (choiceVisit)
		{
		case 1:
		{
			bool inShop = true;
			while (inShop)
			{
				shop->displayItems();
				cout << "���� ���� ���� Gold : " << character->getGold() << "\n";
				cout << "0. ���� ������  1. �����ϱ�  2. �Ǹ��ϱ�  3. ���ֻ������̡�  \n";

				int choiceAction = getValidatedInput("�Է����ּ��� :", 0, 3);

				switch (choiceAction)
				{
					// ���� ������
				case 0:
				{
					cout << "������ �����ϴ�. \n";
					inShop = false;
					askVisitShop = false;
					break;
				}

				// ������ �����ϱ�
				case 1:
				{
					// ����â
					cout << "0. �ڷ� ���ư���";

					for (int i = 0; i < shop->getAvaliableItems().size(); ++i)
					{
						cout << "  " << i + 1 << ". " << shop->getAvaliableItems()[i]->getName() << " �����ϱ�";
					}


					cout << "\n";



					int choiceItem = getValidatedInput("������ �������� �������ּ���. :", 0, shop->getAvaliableItems().size());


					if (choiceItem == 0)
					{
						cout << "���Ÿ� �����մϴ� \n";
						break;
					}
					else
					{
						shop->buyItem(choiceItem - 1, character);
					}

					break;
				}

				// ������ �Ǹ��ϱ�
				case 2:
				{
					// �κ��丮�� ����ִ��� Ȯ���ϱ�
					if (character->getInventory().size() == 0)
					{
						cout << "�Ǹ� ������ �������� �����ϴ�. \n";
						break;
					}


					// �Ǹ�â
					displayInventory(character);

					cout << "\n������ 60% �������� �Ǹ��մϴ�. \n";
					cout << "\n0. �ڷ� ���ư���";

					for (int i = 0; i < character->getInventory().size(); ++i)
					{
						cout << "  " << i + 1 << ". " << character->getInventory()[i]->getName() << " �Ǹ��ϱ�";
					}


					cout << "\n";

					int choiceItem = getValidatedInput("�Ǹ��� �������� �������ּ���. :", 0, character->getInventory().size());

					// �Ǹ� �������� ����
					if (choiceItem == 0)
					{
						cout << "�ǸŸ� �����մϴ�. \n";
						break;
					}
					else
					{
						shop->sellItem(choiceItem - 1, character);
					}

					break;
				}

				case 3:
				{
					shop->playGamble(character);
				}
				default:
				{
					cout << "�߸� �Էµ� ���Դϴ�.\n";
				}

				}
			}
			break;

		}

		case 2:
		{
			cout << "������ �����ϴ�. \n";
			askVisitShop = false;
			break;
		}
		default:
		{
			cout << "�߸� �Էµ� ���Դϴ�.\n";
			cout << "�ٽ� �Է����ּ���. \n";
		}
		}
	}
	askVisitShop = true;
}

int GameManager::getValidatedInput(const string& prompt, int minValue, int maxValue)
{
	int input;
	while (true) {
		cout << prompt;
		cin >> input;

		if (cin.fail() || input < minValue || input > maxValue) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "�߸��� �Է��Դϴ�. �ٽ� �õ����ּ���.\n";
		}
		else {
			break;
		}
	}
	return input;
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