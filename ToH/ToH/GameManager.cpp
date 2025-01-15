#include "GameManager.h"
#include "Item.h"
#include <iostream>
#include <random>
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
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
	//�̸��� ���� ����޼��� ����
	if (monster->getName() == "Dragon")
	{
		cout << "�� �� �� �� �� ���� ";
		cout << "���� Lv." << player->getLevel()<< " " << monster->getName() << " ����!�� �� �� �� �� " << endl;
	}
	else if (monster->getName().find("Elite") != string::npos) {	//find ��� ã�� ���ڰ� ������ npos��ȯ�ϹǷ� !=
		cout << "�� �� �� ����Ʈ ";
		cout << "���� Lv." << player->getLevel() << " " << monster->getName() << " ����! �� �� �� " << endl;
	}
	else {
		cout << "���� Lv." << player->getLevel() << " " << monster->getName() << " ����! " << endl;
	}
	cout << "\n-- Monster status --" << endl;
	cout << "ü��: " << monster->getHealth();
	cout << "\n���ݷ�: " << monster->getAttack() << "\n";
	cout << "----- ------ -----\n\n";

	// ���� ����
	while (true)
	{
		// ���� ���� ���� (������ ü���� 0���� ũ��.)
		if (monster->getHealth() <= 0)
		{
			break;
		}


		int choiceAction;
		cout << "------------------------------\n";
		cout << "1. ����   2. �κ��丮   3. ����â \n";
		cout << "------------------------------\n\n";
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
			int attackChoice;
			cout << "\n���� ����: " << player->getMana() << " / " << player->getMaxMana() << "\n";
			cout << "--------------------------------\n";
			cout << "1. �Ϲݰ��� 2. �Ŀ���Ʈ����ũ(30) 3. ����Ŭ��(60)\n\n";
			cout << "�Է� : ";
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
				cout << "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
				cout << monster->getName() << " óġ!" << endl;


				// ������ �����ϴ� ����
				player->addExperience(experience);
				player->addGold(randomGold);
				cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
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

	cout << "\n";
	cout << " --- Inventory ---" << endl;

	cout << " ��� : " << player->getGold() << " gold\n";
	if (inventory.empty())
	{
		cout << " ������ : ����\n" << endl;

		cout << " --- --------- ---\n\n";
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << ". " << inventory[i]->getName() << " ( " << inventory[i]->getPrice() << " gold ) \n";
	}

	cout << " --- --------- ---\n\n";

	
}

void GameManager::useItemFromInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	int itemIndex;
	if (!inventory.empty())
	{
		cout << "��ȣ�� �Է��Ͽ� ������ ����� �����մϴ�. \n";
	}

	while (true)
	{
		cout << "0���Է��ؼ� �κ��丮 �ݱ� \n\n �Է� : ";
		cin >> itemIndex;

		if (itemIndex > 0 && itemIndex <= inventory.size())
		{
			player->useItem(itemIndex - 1);
			break;
		}
		else if (itemIndex == 0)
		{
			cout << "\n�κ��丮�� �ݽ��ϴ�. \n\n";
			break;
		}
		else
		{
			cout << "�߸��� �Է°��Դϴ�. \n";
		}
	}
}
