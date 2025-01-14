#include "Shop.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "BossMonsterDropItem.h"
#include <vector>
#include <iostream>
#include <random>
#include <cmath>	// gamble()에서 pow()사용

using namespace std;

Shop* Shop::instance = nullptr;

Shop::Shop()	//아이템 추가되면 push_back 필요
{
	avaliableItems.push_back(new AttackBoost);
	avaliableItems.push_back(new HealthPotion);
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
	cout << " --- List ---" << endl;

	for (int i = 0; i < avaliableItems.size(); i++)
	{
		cout << i + 1 << ". " << avaliableItems[i]->getName() << " " << avaliableItems[i]->getPrice() << "원" << endl;
	}

	cout << endl;
}

void Shop::buyItem(int index, Character* player)	// 아이템 추가되면 수정 필요
{
	if (index == 0)
	{
		if (player->getGold() < avaliableItems[0]->getPrice())
		{
			cout << "골드가 모자랍니다." << endl;
			return;
		}

		player->addGold(-50);
		player->addItem(new AttackBoost);

		cout << "AttackBoost를 구매했습니다." << endl;

		return;
	}
	if (index == 1)
	{
		if (player->getGold() < avaliableItems[1]->getPrice())
		{
			cout << "골드가 모자랍니다." << endl;
			return;
		}

		player->addGold(-50);
		player->addItem(new HealthPotion);
		
		cout << "HealthPotion을 구매했습니다." << endl;
	}
}

void Shop::sellItem(int index, Character* player)
{
	vector<Item*>& inventory = player->getInventory();
	Item* item = inventory[index];

	player->addGold(item->getPrice() * 0.6);	//되팔기 가격 60%
	cout << item->getName() << "을 판매했습니다." << endl;
	
	inventory.erase(inventory.begin() + index);
	delete item;
}

void Shop::playGamble(Character* player, int multiple) const
{
	Item* bossMonsterDropItem = new BossMonsterDropItem();
	cout << "\n----------- 주사위 게임 -----------\n" << endl;
	cout << " 1. 주사위를 6번 던집니다.\n" << endl;
	cout << " 2-1. 주사위 눈은 합산됩니다." << endl;
	cout << " 2-2. 중복된 눈이 있으면 제곱됩니다.\n" << endl;
	cout << " 주사위ex) 6 2 6 1 6 2" << endl;
	cout << " 1 + 2 x 2 + 6 x 6 x 6 = 221\n" << endl;
	cout << "------------- 보상 -------------" << endl;
	cout << " 1등 40000↑: " << bossMonsterDropItem->getName() << endl;
	cout << " 2등 10000↑: 공격력 x 100, 체력 x 100" << endl;
	cout << " 3등  1000↑: 공격력 x 10" << endl;
	cout << " 4등   100↑: 10000 골드" << endl;
	cout << " 5등    50↑: 1000 골드\n" << endl;
	cout << "------ 럭키넘버 ------" << endl;
	cout << " 한번 더 + 보상 3배" << endl;
	cout << " 순서x) 1 2 3 4 5 6\n" << endl;
	cout << "----- 언럭키넘버 -----" << endl;
	cout << "      능력치리셋" << endl;;
	cout << " 번호) 1 1 1 1 1 1" << endl;
	cout << " 번호) 2 2 2 2 2 2" << endl;
	cout << " 번호) 3 3 3 3 3 3" << endl;
	cout << "------------------------------" << endl;
	cout << "300 골드를 지불해서 게임을 할 수 있습니다. 소지골드: " << player->getGold() << endl;
	cout << "\nY)한다 ...)안한다: ";

	string action = "";
	cin >> action;

	if (action != "Y" && action != "y")
	{
		cout << "\n돌아갑니다." << endl;
		return;
	}

	if (player->getGold() < 300)
	{
		cout << "\n골드가 부족합니다." << endl;
		return;
	}

	cout << "\n게임을 진행합니다.\n" << endl;

	player->addGold(-300);

	random_device rd;
	uniform_int_distribution<int> randomDice(1, 6);	// 주사위 1 ~ 6

	vector<int> diceNumber;
	int number = 0;

	for (int i = 0; i < 6; i++)
	{
		cout << " " << i + 1 << "번 주사위 던지기 \"" << i + 1 << "\" 입력: ";
		cin >> action;

		cout << endl;

		if (action != to_string(i + 1))
		{
			cout << "잘못된 입력입니다.\n" << endl;
			i--;
			continue;
		}

		// 주사위 굴리기
		number = randomDice(rd);

		cout << " " << number << " 나왔습니다." << endl;

		diceNumber.push_back(number);

		cout << "현재:";

		for (int num : diceNumber)
		{
			cout << " " << num;
		}
		
		cout << "\n" << endl;
	}

	int numCount = 0;	// 주사위 중복 갯수
	int sum = 0;		// 총합 결과값
	bool isLuckyNumber = true;

	for (int i = 0; i < 6; i++)		// O(n²)이지만 반복횟수가 적음
	{
		numCount = 0;
		for (int num : diceNumber)
		{
			if (num - 1 == i)
			{
				numCount++;
			}
		}

		if (numCount == 0)	// 해당 숫자가 없다면 넘어가기
		{
			isLuckyNumber = false;
			continue;
		}

		sum = sum + pow(i + 1, numCount);
	}

	if (isLuckyNumber)
	{
		cout << "\n★럭키넘버★ 재도전 + 보상 3배 획득의 기회!" << endl;
		playGamble(player, multiple * 3);
		return;
	}

	// 언럭키넘버
	if (sum == 1 || sum == 64 || sum == 729)
	{
		int level = player->getLevel();
		player->setLevel(1);
		player->setMaxHealth(200);
		player->setHealth(200);
		player->setAttack(30);
		player->setExperience(0);
		player->setMaxExperience(100);

		cout << "\n언럭키넘버 UnU" << endl;
		cout << "능력치가 초기화 되었습니다..." << endl;
		return;
	}

	cout << "점수: ";

	sort(diceNumber.begin(), diceNumber.end());

	for (int i = 0; i < 5; i++)
	{
		cout << diceNumber[i];

		if (diceNumber[i] == diceNumber[i + 1])
		{
			cout << " x ";
		}

		else
		{
			cout << " + ";
		}
	}

	cout << diceNumber[5] << " = " << sum << "\n" << endl;

	if (sum > 40000 && multiple == 1)
	{
		player->addItem(bossMonsterDropItem);

		cout << "★경축★ 1등 당첨 " << bossMonsterDropItem->getName() << "을 획득합니다!" << endl;

		return;
	}

	delete bossMonsterDropItem;

	if (sum > 40000)
	{
		for (int i = 0; i < multiple; i++)
		{
			player->addItem(new BossMonsterDropItem);
		}

		cout << "★경축★ 1등 당첨 " << bossMonsterDropItem->getName() << "를 " << multiple << "개 획득합니다!" << endl;

		return;
	}

	if (sum > 10000)
	{
		player->setAttack(player->getAttack() * 100 * multiple);
		player->setHealth(player->getHealth() * 100 * multiple);

		cout << "★축★ 2등 당첨 공격력, 체력이 " << 100 * multiple << "배 증가합니다." << endl;

		return;
	}

	if (sum > 1000)
	{
		player->setAttack(player->getAttack() * 10 * multiple);

		cout << "3등 당첨 공격력이 " << 10 * multiple << "배 증가합니다." << endl;

		return;
	}

	if (sum > 100)
	{
		player->addGold(10000 * multiple);

		cout << "4등 당첨 " << 10000 * multiple <<  " 골드를 획득합니다." << endl;

		return;
	}

	if (sum > 50)
	{
		player->addGold(1000 * multiple);

		cout << "5등 당첨 " << 1000 * multiple << " 골드를 획득합니다." << endl;

		return;
	}

	cout << "꽝! >o< 다음 기회에~" << endl;
}

Shop::~Shop()
{
	for (Item*& item : avaliableItems) {
		delete item;
		item = nullptr;
	}

	avaliableItems.clear();
}