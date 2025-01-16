#include "Shop.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "ManaPotion.h"
#include "BossMonsterDropItem.h"
#include "Report.h"
#include <vector>
#include <iostream>
#include <random>
#include <map>
#include <cmath>	// gamble()에서 pow()사용

using namespace std;

Shop* Shop::instance = nullptr;

Shop::Shop() : shopUI(ShopUI::getinstance())	//아이템 추가되면 push_back 필요
{
	avaliableItems.push_back(new AttackBoost);
	avaliableItems.push_back(new HealthPotion);
	avaliableItems.push_back(new ManaPotion);
}

Shop* Shop::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Shop();
	}

	return instance;
}

void Shop::displayItems() const
{
	shopUI.printDisplayItems();
}

void Shop::buyItem(int index, Character* player)	// 아이템 추가되면 수정 필요
{
	if (index == 0)
	{
		if (player->getGold() < avaliableItems[0]->getPrice())
		{
			shopUI.printNotEnoughGold();
			return;
		}

		player->addGold(-50);
		player->addItem(new AttackBoost);
		REPORT->OnItemEvent("AttackBoost", "Acquire");

		//cout << "AttackBoost를 구매했습니다." << endl;

		return;
	}
	if (index == 1)
	{
		if (player->getGold() < avaliableItems[1]->getPrice())
		{
			shopUI.printNotEnoughGold();
			return;
		}

		player->addGold(-50);
		player->addItem(new HealthPotion);
		REPORT->OnItemEvent("HealthPotion", "Acquire");
		
		//cout << "HealthPotion을 구매했습니다." << endl;
	}
	if (index == 2)
	{
		if (player->getGold() < avaliableItems[2]->getPrice())
		{
			shopUI.printNotEnoughGold();
			return;
		}

		player->addGold(-50);
		player->addItem(new ManaPotion);
		REPORT->OnItemEvent("ManaPotion", "Acquire");

		//cout << "ManaPotion을 구매했습니다." << endl;
	}
	// 구매 후 아이템 소모 리포트, 아이템 구매 가격 일괄 50gold 
	REPORT->OnGoldEvent("SpendGold", 50);
}

void Shop::sellItem(int index, Character* player)
{
	vector<Item*>& inventory = player->getInventory();
	Item* item = inventory[index];

	shopUI.printSellltem(item);
	player->addGold(item->getPrice() * 0.6);	//되팔기 가격 60%
	
	inventory.erase(inventory.begin() + index);

	// 판매 완료 시 가격 리포트
	REPORT->OnGoldEvent("EarnGold", item->getPrice() * 0.6);

	// 리포트 후 삭제
	delete item;
}

//럭키넘버 나올 시 재귀문을 쓸수도 있지만 언럭키넘버의 숫자 유지를 위해 재귀문대신 반복문사용
void Shop::playGamble(Character* player) const
{
	Item* bossMonsterDropItem = new BossMonsterDropItem();	// 1등 당첨 시 보상 아이템, 이름 사용을 위해 미리 선언

	string action = "";

	random_device rd;
	uniform_int_distribution<int> randomDice(1, 6);	// 주사위 1 ~ 6

	vector<map<int, int>> unluckyNumbers(3);		// 언럭키넘버 중복 불가

	int randomUnluckyNumber = 0;

	// 언럭키넘버에서 같은 숫자 3개 이하로 나오게 ex) { 6 1 6 6 2 6 }: X, { 6 1 6 6 2 3 }: O
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			randomUnluckyNumber = randomDice(rd);

			if (unluckyNumbers[i].find(randomUnluckyNumber) == unluckyNumbers[i].end())
			{
				unluckyNumbers[i][randomUnluckyNumber] = 1;
			}

			else if (unluckyNumbers[i][randomUnluckyNumber] < 3)
			{
				unluckyNumbers[i][randomUnluckyNumber]++;
			}

			else
			{
				j--;
			}
		}

		// 1 2 3 4 5 6 : 해당 경우는 럭키 넘버이므로 언럭키 넘버가 될 수 없음.
		if (unluckyNumbers[i].size() == 6)
		{
			unluckyNumbers.clear();
			i--;
			continue;
		}

		// 이미 등장한 언럭키 넘버이면 다시 언럭키 넘버 뽑기
		for (int j = 0; j < i; j++)
		{
			if (unluckyNumbers[j] == unluckyNumbers[i])
			{
				unluckyNumbers[i].clear();
				i--;
				break;
			}
		}
	}
	
	cout << "---------------------------------------------------" << endl;
	cout << "\n============= 주사위 게임 =============\n" << endl;
	cout << " 1. 주사위를 6번 던집니다.\n" << endl;
	cout << " 2-1. 주사위 눈은 합산됩니다." << endl;
	cout << " 2-2. 중복된 눈이 있으면 제곱됩니다.\n" << endl;
	cout << " 주사위ex) 6 2 6 1 6 2" << endl;
	cout << " 1 + 2 x 2 + 6 x 6 x 6 = 221\n" << endl;

	int multiple = 1; //럭키넘버가 나올경우 3배수로 올라감

	vector<int> diceNumber;
	map<int, int> diceNumberMap;

	bool isLuckyNumber = false;

	// 럭키넘버가 나올경우 여기서 다시시작
	do
	{
		isLuckyNumber = false;

		cout << "---------------- 보상 ----------------\n" << endl;
		cout << " 1등 10000↑: " << bossMonsterDropItem->getName() << endl;
		cout << " 2등  1000↑: 공격력 x 10" << endl;
		cout << " 3등   100↑: 10000 골드" << endl;
		cout << " 4등    50↑: 1000 골드\n" << endl;
		cout << "--------------------------------------\n" << endl;
		cout << "               순서x\n" << endl;
		cout << " Lucky  1 2 3 4 5 6 : 한번더 + 보상 3배" << endl;

		for (map<int, int>& unluckyNumber : unluckyNumbers)
		{
			cout << "UnLucky ";
			for (pair<int, int> iter : unluckyNumber)
			{
				for (int i = 0; i < iter.second; i++)
				{
					cout << iter.first << " ";
				}
			}
			cout << ": 능력치 리셋" << endl;
		}
		
		cout << "\n==========================================\n" << endl;

		// 처음 들어오면 실행
		if (multiple == 1)
		{
			cout << "300 골드를 지불해서 게임을 할 수 있습니다. 소지골드: " << player->getGold() << endl;

			while (true)
			{
				cout << "\n 1.한다  2.안한다\n";
				cout << "입력 : ";

				cin >> action;

				if (action == "2")
				{
					cout << "\n돌아갑니다." << endl;
					return;
				}

				if (action == "1")
				{
					break;
				}

				cout << "\n잘못된 입력입니다." << endl;
			}
			

			if (player->getGold() < 300)
			{
				shopUI.printNotEnoughGold();
				return;
			}

			player->addGold(-300);
			// 도박 소모 골드 REPORT
			REPORT->OnGoldEvent("SpendGold", 300);
		}

		// 럭키넘버로 인해 두번째 들어올때
		else
		{
			cout << " ★ 럭키넘버★" << endl;
			cout << "재도전 + 보상 3배 획득의 기회!\n" << endl;
		}

		cout << "--------------------------------------\n" << endl;
		cout << "게임을 진행합니다.\n" << endl;
		
		int number = 0;

		// 입력받기
		for (int i = 0; i < 6; i++)
		{
			cout << " " << i + 1 << "번 주사위 던지기 \"" << i + 1 << "\" 입력: ";
			cin >> action;

			cout << endl;

			if (action != to_string(i + 1))
			{
				shopUI.printWrongInput();
				i--;
				continue;
			}

			// 주사위 굴리기
			number = randomDice(rd);

			diceNumber.push_back(number);

			if (diceNumberMap.find(number) == diceNumberMap.end())
			{
				diceNumberMap[number] = 1;
			}

			else
			{
				diceNumberMap[number]++;
			}

			shopUI.printScore(diceNumber);
		}

		// 럭키 넘버 일 때
		if (diceNumberMap.size() == 6)
		{
			multiple *= 3;
			isLuckyNumber = true;
			diceNumber.clear();
			diceNumberMap.clear();
		}

	} while (isLuckyNumber);

	// 언럭키 넘버 체크
	bool isUnluckyNumber = false;

	for (map<int, int>& number : unluckyNumbers)
	{
		if (number == diceNumberMap)
		{
			isUnluckyNumber = true;
		}
	}

	// 언럭키 넘버 일 때
	if (isUnluckyNumber)
	{
		int level = player->getLevel();
		player->setLevel(1);
		player->setMaxHealth(200);
		player->setHealth(200);
		player->setAttack(30);
		player->setExperience(0);
		player->setMaxExperience(100);

		shopUI.printUnluckyNumber();

		delete bossMonsterDropItem;

		return;
	}

	// 럭키/언럭키 넘버가 아닐 때
	int sum = 0; // 총합 결과값

	for (pair<int, int> num : diceNumberMap)
	{
		sum = sum + pow(num.first, num.second);
	}

	// 점수 계산식과 합계 출력
	shopUI.printDisplaySum(diceNumber, sum);

	shopUI.printGamblePrize(sum, multiple);

	// 1등
	if (sum > 10000 && multiple == 1)
	{
		player->addItem(bossMonsterDropItem);

		return;
	}

	if (sum > 10000)
	{
		player->addItem(bossMonsterDropItem);

		for (int i = 0; i < multiple - 1; i++)
		{
			player->addItem(new BossMonsterDropItem);
		}

		return;
	}

	delete bossMonsterDropItem;

	// 2등
	if (sum > 1000)
	{
		player->setAttack(player->getAttack() * 10 * multiple);
		return;
	}

	// 3등
	if (sum > 100)
	{
		player->addGold(10000 * multiple);
		REPORT->OnGoldEvent("EarnGold", 10000 * multiple);
		return;
	}

	// 4등
	if (sum > 50)
	{
		player->addGold(1000 * multiple);
		REPORT->OnGoldEvent("EarnGold", 1000 * multiple);
		return;
	}

	// 꽝
	
}


vector<Item*> Shop::getAvaliableItems()
{
	return avaliableItems;
}

Shop::~Shop()
{
	for (Item*& item : avaliableItems) {
		delete item;
		item = nullptr;
	}

	avaliableItems.clear();
}