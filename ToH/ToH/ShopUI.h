#pragma once

#include "Item.h"
#include <vector>

class ShopUI
{
private:
	ShopUI();
	ShopUI(const ShopUI&) = delete;
	ShopUI& operator=(const ShopUI&) = delete;

public:
	static ShopUI& getinstance();
	void printDisplayItems();
	void printNotEnoughGold();
	void printBuyItem(Item* item);
	void printSellltem(Item* item);
	void printWrongInput();
	void printScore(vector<int>& numbers);
	void printDisplaySum(vector<int>& numbers, int sum);
	void printGamblePrize(int score, int multiple);
	void printUnluckyNumber();
};