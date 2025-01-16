#include "ShopUI.h"
#include "Shop.h"

ShopUI::ShopUI()
{
}

ShopUI& ShopUI::getinstance()
{
	static ShopUI shopUI;

	return shopUI;
	// TODO: 여기에 return 문을 삽입합니다.
}

void ShopUI::printDisplayItems()
{
	cout << "        --------- List ---------" << endl;

	vector<Item*> avaliableItems = (Shop::getInstance())->getAvaliableItems();

	if (avaliableItems.empty())
	{
		cout << "        There are no items available for sale.\n";
		return;
	}

	for (int i = 0; i < avaliableItems.size(); i++)
	{
		cout << "        " << i + 1 << ". " << avaliableItems[i]->getName() << " " << avaliableItems[i]->getPrice() << " gold" << endl;
	}

	cout << "        ------------------------" << endl;

	cout << endl;
}

void ShopUI::printNotEnoughGold()
{
	cout << "골드가 모자랍니다." << endl;
}

void ShopUI::printBuyItem(Item* item)
{
	cout << item->getName() << "을 구매했습니다." << endl;
}

void ShopUI::printSellltem(Item* item)
{
	cout << "\n" << item->getName() << "을 판매했습니다.";
}

void ShopUI::printWrongInput()
{
	cout << "잘못된 입력입니다.\n" << endl;
}

void ShopUI::printScore(vector<int>& numbers)
{
	cout << " " << numbers.back() << " 나왔습니다." << endl;

	cout << "현재:";

	for (int num : numbers)
	{
		cout << " " << num;
	}

	cout << "\n" << endl;
}

void ShopUI::printDisplaySum(vector<int>& numbers, int sum)
{
	cout << "점수: ";

	sort(numbers.begin(), numbers.end());

	for (int i = 0; i < 5; i++)
	{
		cout << numbers[i];

		if (numbers[i] == numbers[i + 1])
		{
			cout << " x ";
		}

		else
		{
			cout << " + ";
		}
	}

	cout << numbers[5] << " = " << sum << "\n" << endl;
}

void ShopUI::printGamblePrize(int score, int multiple)
{
	cout << "----------------------------------------\n\n ";

	// 1등
	if (score > 10000)
	{
		cout << "★ 경축★ 1등 당첨" << endl;

		return;
	}

	// 2등
	if (score > 1000)
	{
		cout << "2등 당첨" << endl;

		return;
	}

	// 3등
	if (score > 100)
	{
		cout << "3등 당첨";

		return;
	}

	// 4등
	if (score > 50)
	{
		cout << "4등 당첨";

		return;
	}

	if (score > 25)
	{
		cout << "5등 당첨";

		return;
	}
	// 꽝
	cout << "꽝! >o< 다음 기회에~" << endl;
}

void ShopUI::printUnluckyNumber()
{
	cout << "\n언럭키넘버 UnU" << endl;
	cout << "능력치가 초기화 되었습니다..." << endl;
}
