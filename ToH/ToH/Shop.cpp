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
#include <cmath>	// gamble()���� pow()���

using namespace std;

Shop* Shop::instance = nullptr;

Shop::Shop() : shopUI(ShopUI::getinstance())	//������ �߰��Ǹ� push_back �ʿ�
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

void Shop::buyItem(int index, Character* player)	// ������ �߰��Ǹ� ���� �ʿ�
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

		//cout << "AttackBoost�� �����߽��ϴ�." << endl;

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
		
		//cout << "HealthPotion�� �����߽��ϴ�." << endl;
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

		//cout << "ManaPotion�� �����߽��ϴ�." << endl;
	}
	// ���� �� ������ �Ҹ� ����Ʈ, ������ ���� ���� �ϰ� 50gold 
	REPORT->OnGoldEvent("SpendGold", 50);
}

void Shop::sellItem(int index, Character* player)
{
	vector<Item*>& inventory = player->getInventory();
	Item* item = inventory[index];

	shopUI.printSellltem(item);
	player->addGold(item->getPrice() * 0.6);	//���ȱ� ���� 60%
	
	inventory.erase(inventory.begin() + index);

	// �Ǹ� �Ϸ� �� ���� ����Ʈ
	REPORT->OnGoldEvent("EarnGold", item->getPrice() * 0.6);

	// ����Ʈ �� ����
	delete item;
}

//��Ű�ѹ� ���� �� ��͹��� ������ ������ ��Ű�ѹ��� ���� ������ ���� ��͹���� �ݺ������
void Shop::playGamble(Character* player) const
{
	Item* bossMonsterDropItem = new BossMonsterDropItem();	// 1�� ��÷ �� ���� ������, �̸� ����� ���� �̸� ����

	string action = "";

	random_device rd;
	uniform_int_distribution<int> randomDice(1, 6);	// �ֻ��� 1 ~ 6

	vector<map<int, int>> unluckyNumbers(3);		// ��Ű�ѹ� �ߺ� �Ұ�

	int randomUnluckyNumber = 0;

	// ��Ű�ѹ����� ���� ���� 3�� ���Ϸ� ������ ex) { 6 1 6 6 2 6 }: X, { 6 1 6 6 2 3 }: O
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

		// 1 2 3 4 5 6 : �ش� ���� ��Ű �ѹ��̹Ƿ� ��Ű �ѹ��� �� �� ����.
		if (unluckyNumbers[i].size() == 6)
		{
			unluckyNumbers.clear();
			i--;
			continue;
		}

		// �̹� ������ ��Ű �ѹ��̸� �ٽ� ��Ű �ѹ� �̱�
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
	cout << "\n============= �ֻ��� ���� =============\n" << endl;
	cout << " 1. �ֻ����� 6�� �����ϴ�.\n" << endl;
	cout << " 2-1. �ֻ��� ���� �ջ�˴ϴ�." << endl;
	cout << " 2-2. �ߺ��� ���� ������ �����˴ϴ�.\n" << endl;
	cout << " �ֻ���ex) 6 2 6 1 6 2" << endl;
	cout << " 1 + 2 x 2 + 6 x 6 x 6 = 221\n" << endl;

	int multiple = 1; //��Ű�ѹ��� ���ð�� 3����� �ö�

	vector<int> diceNumber;
	map<int, int> diceNumberMap;

	bool isLuckyNumber = false;

	// ��Ű�ѹ��� ���ð�� ���⼭ �ٽý���
	do
	{
		isLuckyNumber = false;

		cout << "---------------- ���� ----------------\n" << endl;
		cout << " 1�� 10000��: " << bossMonsterDropItem->getName() << endl;
		cout << " 2��  1000��: ���ݷ� x 10" << endl;
		cout << " 3��   100��: 10000 ���" << endl;
		cout << " 4��    50��: 1000 ���\n" << endl;
		cout << "--------------------------------------\n" << endl;
		cout << "               ����x\n" << endl;
		cout << " Lucky  1 2 3 4 5 6 : �ѹ��� + ���� 3��" << endl;

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
			cout << ": �ɷ�ġ ����" << endl;
		}
		
		cout << "\n==========================================\n" << endl;

		// ó�� ������ ����
		if (multiple == 1)
		{
			cout << "300 ��带 �����ؼ� ������ �� �� �ֽ��ϴ�. �������: " << player->getGold() << endl;

			while (true)
			{
				cout << "\n 1.�Ѵ�  2.���Ѵ�\n";
				cout << "�Է� : ";

				cin >> action;

				if (action == "2")
				{
					cout << "\n���ư��ϴ�." << endl;
					return;
				}

				if (action == "1")
				{
					break;
				}

				cout << "\n�߸��� �Է��Դϴ�." << endl;
			}
			

			if (player->getGold() < 300)
			{
				shopUI.printNotEnoughGold();
				return;
			}

			player->addGold(-300);
			// ���� �Ҹ� ��� REPORT
			REPORT->OnGoldEvent("SpendGold", 300);
		}

		// ��Ű�ѹ��� ���� �ι�° ���ö�
		else
		{
			cout << " �� ��Ű�ѹ���" << endl;
			cout << "�絵�� + ���� 3�� ȹ���� ��ȸ!\n" << endl;
		}

		cout << "--------------------------------------\n" << endl;
		cout << "������ �����մϴ�.\n" << endl;
		
		int number = 0;

		// �Է¹ޱ�
		for (int i = 0; i < 6; i++)
		{
			cout << " " << i + 1 << "�� �ֻ��� ������ \"" << i + 1 << "\" �Է�: ";
			cin >> action;

			cout << endl;

			if (action != to_string(i + 1))
			{
				shopUI.printWrongInput();
				i--;
				continue;
			}

			// �ֻ��� ������
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

		// ��Ű �ѹ� �� ��
		if (diceNumberMap.size() == 6)
		{
			multiple *= 3;
			isLuckyNumber = true;
			diceNumber.clear();
			diceNumberMap.clear();
		}

	} while (isLuckyNumber);

	// ��Ű �ѹ� üũ
	bool isUnluckyNumber = false;

	for (map<int, int>& number : unluckyNumbers)
	{
		if (number == diceNumberMap)
		{
			isUnluckyNumber = true;
		}
	}

	// ��Ű �ѹ� �� ��
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

	// ��Ű/��Ű �ѹ��� �ƴ� ��
	int sum = 0; // ���� �����

	for (pair<int, int> num : diceNumberMap)
	{
		sum = sum + pow(num.first, num.second);
	}

	// ���� ���İ� �հ� ���
	shopUI.printDisplaySum(diceNumber, sum);

	shopUI.printGamblePrize(sum, multiple);

	// 1��
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

	// 2��
	if (sum > 1000)
	{
		player->setAttack(player->getAttack() * 10 * multiple);
		return;
	}

	// 3��
	if (sum > 100)
	{
		player->addGold(10000 * multiple);
		REPORT->OnGoldEvent("EarnGold", 10000 * multiple);
		return;
	}

	// 4��
	if (sum > 50)
	{
		player->addGold(1000 * multiple);
		REPORT->OnGoldEvent("EarnGold", 1000 * multiple);
		return;
	}

	// ��
	
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