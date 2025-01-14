#include "Shop.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include "BossMonsterDropItem.h"
#include <vector>
#include <iostream>
#include <random>
#include <cmath>	// gamble()���� pow()���

using namespace std;

Shop* Shop::instance = nullptr;

Shop::Shop()	//������ �߰��Ǹ� push_back �ʿ�
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
		cout << i + 1 << ". " << avaliableItems[i]->getName() << " " << avaliableItems[i]->getPrice() << "��" << endl;
	}

	cout << endl;
}

void Shop::buyItem(int index, Character* player)	// ������ �߰��Ǹ� ���� �ʿ�
{
	if (index == 0)
	{
		if (player->getGold() < avaliableItems[0]->getPrice())
		{
			cout << "��尡 ���ڶ��ϴ�." << endl;
			return;
		}

		player->addGold(-50);
		player->addItem(new AttackBoost);

		cout << "AttackBoost�� �����߽��ϴ�." << endl;

		return;
	}
	if (index == 1)
	{
		if (player->getGold() < avaliableItems[1]->getPrice())
		{
			cout << "��尡 ���ڶ��ϴ�." << endl;
			return;
		}

		player->addGold(-50);
		player->addItem(new HealthPotion);
		
		cout << "HealthPotion�� �����߽��ϴ�." << endl;
	}
}

void Shop::sellItem(int index, Character* player)
{
	vector<Item*>& inventory = player->getInventory();
	Item* item = inventory[index];

	player->addGold(item->getPrice() * 0.6);	//���ȱ� ���� 60%
	cout << item->getName() << "�� �Ǹ��߽��ϴ�." << endl;
	
	inventory.erase(inventory.begin() + index);
	delete item;
}

void Shop::playGamble(Character* player, int multiple) const
{
	Item* bossMonsterDropItem = new BossMonsterDropItem();
	cout << "\n----------- �ֻ��� ���� -----------\n" << endl;
	cout << " 1. �ֻ����� 6�� �����ϴ�.\n" << endl;
	cout << " 2-1. �ֻ��� ���� �ջ�˴ϴ�." << endl;
	cout << " 2-2. �ߺ��� ���� ������ �����˴ϴ�.\n" << endl;
	cout << " �ֻ���ex) 6 2 6 1 6 2" << endl;
	cout << " 1 + 2 x 2 + 6 x 6 x 6 = 221\n" << endl;
	cout << "------------- ���� -------------" << endl;
	cout << " 1�� 40000��: " << bossMonsterDropItem->getName() << endl;
	cout << " 2�� 10000��: ���ݷ� x 100, ü�� x 100" << endl;
	cout << " 3��  1000��: ���ݷ� x 10" << endl;
	cout << " 4��   100��: 10000 ���" << endl;
	cout << " 5��    50��: 1000 ���\n" << endl;
	cout << "------ ��Ű�ѹ� ------" << endl;
	cout << " �ѹ� �� + ���� 3��" << endl;
	cout << " ����x) 1 2 3 4 5 6\n" << endl;
	cout << "----- ��Ű�ѹ� -----" << endl;
	cout << "      �ɷ�ġ����" << endl;;
	cout << " ��ȣ) 1 1 1 1 1 1" << endl;
	cout << " ��ȣ) 2 2 2 2 2 2" << endl;
	cout << " ��ȣ) 3 3 3 3 3 3" << endl;
	cout << "------------------------------" << endl;
	cout << "300 ��带 �����ؼ� ������ �� �� �ֽ��ϴ�. �������: " << player->getGold() << endl;
	cout << "\nY)�Ѵ� ...)���Ѵ�: ";

	string action = "";
	cin >> action;

	if (action != "Y" && action != "y")
	{
		cout << "\n���ư��ϴ�." << endl;
		return;
	}

	if (player->getGold() < 300)
	{
		cout << "\n��尡 �����մϴ�." << endl;
		return;
	}

	cout << "\n������ �����մϴ�.\n" << endl;

	player->addGold(-300);

	random_device rd;
	uniform_int_distribution<int> randomDice(1, 6);	// �ֻ��� 1 ~ 6

	vector<int> diceNumber;
	int number = 0;

	for (int i = 0; i < 6; i++)
	{
		cout << " " << i + 1 << "�� �ֻ��� ������ \"" << i + 1 << "\" �Է�: ";
		cin >> action;

		cout << endl;

		if (action != to_string(i + 1))
		{
			cout << "�߸��� �Է��Դϴ�.\n" << endl;
			i--;
			continue;
		}

		// �ֻ��� ������
		number = randomDice(rd);

		cout << " " << number << " ���Խ��ϴ�." << endl;

		diceNumber.push_back(number);

		cout << "����:";

		for (int num : diceNumber)
		{
			cout << " " << num;
		}
		
		cout << "\n" << endl;
	}

	int numCount = 0;	// �ֻ��� �ߺ� ����
	int sum = 0;		// ���� �����
	bool isLuckyNumber = true;

	for (int i = 0; i < 6; i++)		// O(n��)������ �ݺ�Ƚ���� ����
	{
		numCount = 0;
		for (int num : diceNumber)
		{
			if (num - 1 == i)
			{
				numCount++;
			}
		}

		if (numCount == 0)	// �ش� ���ڰ� ���ٸ� �Ѿ��
		{
			isLuckyNumber = false;
			continue;
		}

		sum = sum + pow(i + 1, numCount);
	}

	if (isLuckyNumber)
	{
		cout << "\n�ڷ�Ű�ѹ��� �絵�� + ���� 3�� ȹ���� ��ȸ!" << endl;
		playGamble(player, multiple * 3);
		return;
	}

	// ��Ű�ѹ�
	if (sum == 1 || sum == 64 || sum == 729)
	{
		int level = player->getLevel();
		player->setLevel(1);
		player->setMaxHealth(200);
		player->setHealth(200);
		player->setAttack(30);
		player->setExperience(0);
		player->setMaxExperience(100);

		cout << "\n��Ű�ѹ� UnU" << endl;
		cout << "�ɷ�ġ�� �ʱ�ȭ �Ǿ����ϴ�..." << endl;
		return;
	}

	cout << "����: ";

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

		cout << "�ڰ���� 1�� ��÷ " << bossMonsterDropItem->getName() << "�� ȹ���մϴ�!" << endl;

		return;
	}

	delete bossMonsterDropItem;

	if (sum > 40000)
	{
		for (int i = 0; i < multiple; i++)
		{
			player->addItem(new BossMonsterDropItem);
		}

		cout << "�ڰ���� 1�� ��÷ " << bossMonsterDropItem->getName() << "�� " << multiple << "�� ȹ���մϴ�!" << endl;

		return;
	}

	if (sum > 10000)
	{
		player->setAttack(player->getAttack() * 100 * multiple);
		player->setHealth(player->getHealth() * 100 * multiple);

		cout << "����� 2�� ��÷ ���ݷ�, ü���� " << 100 * multiple << "�� �����մϴ�." << endl;

		return;
	}

	if (sum > 1000)
	{
		player->setAttack(player->getAttack() * 10 * multiple);

		cout << "3�� ��÷ ���ݷ��� " << 10 * multiple << "�� �����մϴ�." << endl;

		return;
	}

	if (sum > 100)
	{
		player->addGold(10000 * multiple);

		cout << "4�� ��÷ " << 10000 * multiple <<  " ��带 ȹ���մϴ�." << endl;

		return;
	}

	if (sum > 50)
	{
		player->addGold(1000 * multiple);

		cout << "5�� ��÷ " << 1000 * multiple << " ��带 ȹ���մϴ�." << endl;

		return;
	}

	cout << "��! >o< ���� ��ȸ��~" << endl;
}

Shop::~Shop()
{
	for (Item*& item : avaliableItems) {
		delete item;
		item = nullptr;
	}

	avaliableItems.clear();
}