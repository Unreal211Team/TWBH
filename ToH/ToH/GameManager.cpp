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

	// 진화 : 몬스터 Elite화 확인 30%확률
	Evolve evolver;
	monster = evolver.evolve(monster);

	return monster;
}

void GameManager::battle(Character* player, Monster* monster)
{
	BuffManager* manager = BuffManager::getInstance();

	int experience = 50;// 몬스터 고정 경험치 50
	int itemDrop = 30;	// 아이템 드롭 확률 30퍼

	random_device rd;
	uniform_int_distribution<int> randomG(10, 20);
	uniform_int_distribution<int> randomI(1, 100);

	int randomGold = randomG(rd);
	//이름에 따라 등장메세지 구분
	if (monster->getName() == "Dragon")
	{
		cout << "☆ ★ ☆ ★ ☆ 보스 ";
		cout << "몬스터 " << monster->getName() << " 등장! ☆ ★ ☆ ★ ☆ " << endl;
		monster->displayArt();
	}
	else if (monster->getName().find("Elite") != string::npos) {	//find 사용 찾는 문자가 있으면 npos반환하므로 !=
		cout << "☆ ★ ☆ 엘리트 ";
		cout << "몬스터 " << monster->getName() << " 등장! ☆ ★ ☆ " << endl;
		monster->displayArt();
	}
	else {
		cout << "몬스터 " << monster->getName() << " 등장! " << endl;
		monster->displayArt();
	}

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

		cout << "1. 공격   2. 인벤토리   3. 상태창 \n";

		int choiceAction = getValidatedInput("입력해주세요 :", 0, 3);

		switch (choiceAction)
		{

			// 1. 공격 선택 
		case 1:
		{
			int attackChoice;
			cout << "\n현재 마나: " << player->getMana() << " / " << player->getMaxMana() << "\n";
			cout << "1. 일반공격  2. 파워스트라이크(30) 3. 매직클로(60)\n";
			cout << "공격 선택 : ";
			cin >> attackChoice;

			switch (attackChoice)
			{
			case 1:
				cout << player->getName() << "이(가) ";
				monster->takeDamage(player->getAttack());
				break;
			case 2:
			{
				PowerStrike powerStrike;
				powerStrike.use(player, monster);
				if (player->getMana() < powerStrike.getMana())
				{
					cout << "다른 선택을 하세요.\n";
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
					cout << "다른 선택을 하세요.\n";
					continue;
				}
				break;
			}
			default:
				cout << "잘못된 입력입니다.\n";
				continue;
			}

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

			AttackModeMonsterFactory& attackModeMonsterFactory = AttackModeMonsterFactory::getInstance();
			shared_ptr<ActingMonster> tempMonster = attackModeMonsterFactory.getRandomMonster(*monster);

			// 몬스터의 공격
			cout << monster->getName() << "이(가) ";
			player->takeDamage(tempMonster->getAttack());
			tempMonster->doAttack();

			cout << "플레이어의 체력 :" << player->getHealth() << endl;
			// 몬스터의 공격에 플레이어가 사망했는지 확인하는 로직
			if (player->getHealth() == 0)
			{
				player->isDead();
				return;
			}

			cout << "\nHP: " << player->getHealth() << "/" << player->getMaxHealth();
			cout << "  EXP: " << player->getExperience() << "/" << player->getMaxExperience();
			cout << "  골드: " << player->getGold() << "원" << endl;

			if (manager->ActiveBuffsCheck())
			{
				manager->updateBuffs(player);
			}

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

		if (manager->ActiveBuffsCheck())
		{
			manager->updateBuffs(player);
		}

		// 플레이어가 죽었을 때
		if (player->getHealth() == 0)
		{
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


void GameManager::visitShop(Character* character, Shop* shop)
{
	bool askVisitShop = true;

	while (askVisitShop)
	{
		cout << "\n==================================================\n" << endl;
		cout << "상점을 방문하시겠습니까?" << endl;
		cout << "1. 한다 \n";
		cout << "2. 안한다. \n";

		int choiceVisit = getValidatedInput("입력해주세요 :", 1, 2);

		switch (choiceVisit)
		{
		case 1:
		{
			bool inShop = true;
			while (inShop)
			{
				shop->displayItems();
				cout << "현재 보유 중인 Gold : " << character->getGold() << "\n";
				cout << "0. 상점 나가기  1. 구매하기  2. 판매하기  3. ★주사위놀이★  \n";

				int choiceAction = getValidatedInput("입력해주세요 :", 0, 3);

				switch (choiceAction)
				{
					// 상점 나가기
				case 0:
				{
					cout << "상점을 나갑니다. \n";
					inShop = false;
					askVisitShop = false;
					break;
				}

				// 아이템 구매하기
				case 1:
				{
					// 구매창
					cout << "0. 뒤로 돌아가기";

					for (int i = 0; i < shop->getAvaliableItems().size(); ++i)
					{
						cout << "  " << i + 1 << ". " << shop->getAvaliableItems()[i]->getName() << " 구매하기";
					}


					cout << "\n";



					int choiceItem = getValidatedInput("구매할 아이템을 선택해주세요. :", 0, shop->getAvaliableItems().size());


					if (choiceItem == 0)
					{
						cout << "구매를 종료합니다 \n";
						break;
					}
					else
					{
						shop->buyItem(choiceItem - 1, character);
					}

					break;
				}

				// 아이템 판매하기
				case 2:
				{
					// 인벤토리가 비어있는지 확인하기
					if (character->getInventory().size() == 0)
					{
						cout << "판매 가능한 아이템이 없습니다. \n";
						break;
					}


					// 판매창
					displayInventory(character);

					cout << "\n원가의 60% 가격으로 판매합니다. \n";
					cout << "\n0. 뒤로 돌아가기";

					for (int i = 0; i < character->getInventory().size(); ++i)
					{
						cout << "  " << i + 1 << ". " << character->getInventory()[i]->getName() << " 판매하기";
					}


					cout << "\n";

					int choiceItem = getValidatedInput("판매할 아이템을 선택해주세요. :", 0, character->getInventory().size());

					// 판매 이전으로 가기
					if (choiceItem == 0)
					{
						cout << "판매를 종료합니다. \n";
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
					cout << "잘못 입력된 값입니다.\n";
				}

				}
			}
			break;

		}

		case 2:
		{
			cout << "상점을 나갑니다. \n";
			askVisitShop = false;
			break;
		}
		default:
		{
			cout << "잘못 입력된 값입니다.\n";
			cout << "다시 입력해주세요. \n";
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
			cout << "잘못된 입력입니다. 다시 시도해주세요.\n";
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