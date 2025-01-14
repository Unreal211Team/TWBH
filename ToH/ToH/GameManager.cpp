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
	cout << ", 공격력: " << monster->getAttack() << endl;
	
	string action = "";

	bool isDigit = false;	//입력값이 숫자인지 아닌지 판단할 때 쓰임
	int act = 0;

	while (true) {

		cout << "\n1)공격 2)인벤토리 3)상태창\n";
		cout << "입력: ";

		cin >> action;

		cout << endl;

		if (action != "1" && action != "2" && action != "3")
		{
			cout << "잘못된 입력입니다." << endl;
			continue;
		}

		// 입력 값 2. 인벤토리 - 아이템 사용
		if (action == "2")
		{
			displayInventory(player);

			if (player->getInventory().size() == 0)
			{
				continue;
			}

			cout << "\n숫자)해당 아이템 사용 Q)나가기";
			cout << "입력: ";

			cin >> action;

			if (action == "Q" || action == "q")
			{
				continue;
			}

			// 입력 값이 숫자인지 판별
			isDigit = true;

			for (char actionChar : action)
			{
				if (!isdigit(actionChar))
				{
					isDigit = false;
					break;
				}
			}

			// 입력 값이 숫자가 아니라면
			if (!isDigit)
			{
				cout << "잘못된 입력입니다." << endl;
				continue;
			}

			act = stoi(action);

			if (act > player->getInventory().size() || act <= 0)
			{
				cout << "잘못된 입력입니다." << endl;
				continue;
			}

			player->useItem(act - 1);

			continue;
		}

		// 입력 값 3. 스테이터스 출력
		if (action == "3")
		{
			player->displayStatus();
			continue;
		}

		/*
		* 나머지 - 입력 값 1. 공격
		* 플레이어가 몬스터 공격
		*/

		monster->takeDamage(player->getAttack());

		// 몬스터가 죽었을 때
		if (monster->getHealth() == 0)
		{
			cout << player->getName() << "가 ";
			cout << monster->getName() << "을 공격합니다! ";
			cout << monster->getName() << " 처치!" << endl;

			// 보스를 잡았을 때
			if (monster->getName()=="Dragon")
			{
				Item* drop = monster->dropItem();
				cout << player->getName() << "가 \"";
				cout << drop->getName() << "\"를 획득했습니다." << endl;
				player->addItem(drop);
				cout << "\n영웅 " << player->getName() << "에 의해 세계의 평화가 지켜졌다." << endl;
				break;
			}

			player->addExperience(experience);
			player->addGold(randomGold);
			
			cout << player->getName() << "가 ";
			cout << experience << " EXP와 ";
			cout << randomGold << " 골드를 획득했습니다." << endl;

			if (randomI(rd) <= 30)
			{
				Item* drop = monster->dropItem();
				cout << player->getName() << "가 \"";
				cout << drop->getName() << "\"을 획득했습니다." << endl;
				player->addItem(drop);
			}

			// 캐릭터 레벨업
			if (player->IsLevelUp())
			{
				player->levelUp();
				cout << player->getName() << "가 레벨업! ";
				cout << "Lv." << player->getLevel() << endl;
			}

			cout << "\nHP: " << player->getHealth() << "/" << player->getMaxHealth();
			cout << "  EXP: " << player->getExperience() << "/" << player->getMaxExperience();
			cout << "  골드: " << player->getGold() << "원" << endl;

			break;
		}

		cout << player->getName() << "가 ";
		cout << monster->getName() << "을 공격합니다! ";
		cout << monster->getName() << " 체력: " << monster->getHealth() << endl;


		/*
		* 몬스터가 플레이어 공격
		*/
		
		player->takeDamage(monster->getAttack());

		cout << monster->getName() << "이 ";
		cout << player->getName() << "을 공격합니다! ";
		cout << player->getName() << " 체력: " << player->getHealth() << endl;

		// 플레이어가 죽었을 때
		if (player->getHealth() == 0)
		{
			cout << player->getName() << "가 사망했습니다. 게임 오버!" << endl;
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
		cout << " 없음\n" << endl;
		return;
	}

	for (int i = 0; i < inventory.size(); i++)
	{
		cout << i + 1 << ". " << inventory[i]->getName() << " " << inventory[i]->getPrice() << "원" << endl;
	}

	cout << endl;
}