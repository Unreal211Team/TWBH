#include "Shop.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include <vector>
#include <iostream>

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
	cout << "--- List ---" << endl;

	if (avaliableItems.empty())
	{
		cout << "There are no items available for sale.\n";
		return;
	}

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

Shop::~Shop()
{
	for (Item*& item : avaliableItems) {
		delete item;
		item = nullptr;
	}

	avaliableItems.clear();
}