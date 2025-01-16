#pragma once

#include <vector>
#include "Item.h"
#include "Character.h"
#include "ShopUI.h"

class Shop
{
private:
	static Shop* instance;
	vector<Item*> avaliableItems;
	ShopUI& shopUI;

	Shop();
	Shop(const Shop&) = delete;
	Shop& operator=(const Shop&) = delete;

public:
	static Shop* getInstance();
	void displayItems() const;
	void buyItem(int index, Character* player);
	void sellItem(int index, Character* player);
	void playGamble(Character* player) const;

	vector<Item*> getAvaliableItems();

	~Shop();
};