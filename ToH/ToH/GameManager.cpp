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
	int experience = 50;// 몬스터 고정 경험치 50
	int itemDrop = 30;	// 아이템 드롭 확률 30퍼

	random_device rd;
	uniform_int_distribution<int> randomG(10, 20);
	uniform_int_distribution<int> randomI(1, 100);

	int randomGold = randomG(rd);

	if (monster->getName() == "Dragon")
	{
		cout << "보스 ";
	}

	cout << "몬스터 " << monster->getName() << " 등장! ";
	cout << "체력: " << monster->getHealth();
	cout << ", 공격력: " << monster->getAttack() << "\n";


	// 전투 로직
	while (true)
	{
		// 전투 시작 조건 (몬스터의 체력이 0보다 크다.)
		if (monster->getHealth() <= 0)
		{
			break;
		}


		int choiceAction;

		cout << "1. 공격   2. 인벤토리   3. 상태창 \n";
		cout << "입력 : ";

		while (true) 
		{
			cin >> choiceAction;

			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "잘못 입력된 값입니다.\n";
				cout << "다시 입력해주세요. :";
			}
			else
			{
				break;
			}
		}

		

		switch (choiceAction)
		{

			// 1. 공격 선택 
		case 1:
		{



			// 플레이어의 공격
			cout << player->getName() << "이(가) ";
			monster->takeDamage(player->getAttack());

			// 플레이어의 공격에 몬스터가 죽었을 때
			if (monster->getHealth() == 0)
			{
				cout << monster->getName() << " 처치!" << endl;


				// 보상을 지급하는 로직
				player->addExperience(experience);
				player->addGold(randomGold);

				if (randomI(rd) <= itemDrop)
				{
					Item* drop = monster->dropItem();
					player->addItem(drop);
				}

				// 캐릭터 레벨업 확인하는 로직
				if (player->IsLevelUp())
				{
					player->levelUp();
				}

				// 죽은 몬스터가 보스인지 확인하는 로직
				if (monster->getName() == "Dragon")
				{
					cout << "\n영웅 " << player->getName() << "에 의해 세계의 평화가 지켜졌다." << endl;
					break;
				}
				return;
			}


			// 몬스터의 공격
			cout << monster->getName() << "이(가) ";
			player->takeDamage(monster->getAttack());

			// 몬스터의 공격에 플레이어가 사망했는지 확인하는 로직
			if (player->getHealth() == 0)
			{
				player->isDead();
				return;
			}
			break;
		}

		// 2. 인벤토리 선택
		case 2:
		{
			displayInventory(player);
			useItemFromInventory(player);
			break;
		}


		// 3. 상태창 선택
		case 3:
		{
			player->displayStatus();
			break;
		}
		default:
		{
			cout << "잘못된 입력값입니다. \n";
			break;
		}

		// 전투가 끝나면 몬스터 객체를 삭제
		delete monster;
		monster = nullptr;
		}
	}
}



void GameManager::displayInventory(Character* player)
{
	vector<Item*> inventory = player->getInventory();

	cout << " --- Inventory ---" << endl;

	cout << " 소지골드 : " << player->getGold() << " gold\n";

	if (inventory.empty())
	{
		cout << " 소지 아이템 : 없음\n" << endl;
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

	cout << "번호를 입력하여 아이템 사용이 가능합니다. \n";

	while (true)
	{
		cout << "0. 인벤토리 닫기 \n";
		cin >> itemIndex;

		if (itemIndex > 0 && itemIndex <= inventory.size())
		{
			player->useItem(itemIndex - 1);
			break;
		}
		else if (itemIndex == 0)
		{
			cout << "인벤토리를 닫습니다. \n";
			break;
		}
		else
		{
			cout << "잘못된 입력값입니다. \n";
		}
	}
}
