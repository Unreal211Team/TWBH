#include "Shop.h"
#include "AttackBoost.h"
#include "HealthPotion.h"
#include <vector>
#include <iostream>

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
	cout << "--- List ---" << endl;

	if (avaliableItems.empty())
	{
		cout << "There are no items available for sale.\n";
		return;
	}

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

Shop::~Shop()
{
	for (Item*& item : avaliableItems) {
		delete item;
		item = nullptr;
	}

	avaliableItems.clear();
}