#include "ShopUI.h"
#include "Shop.h"

ShopUI::ShopUI()
{
}

ShopUI& ShopUI::getinstance()
{
	static ShopUI shopUI;

	return shopUI;
	// TODO: ���⿡ return ���� �����մϴ�.
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
	cout << "��尡 ���ڶ��ϴ�." << endl;
}

void ShopUI::printBuyItem(Item* item)
{
	cout << item->getName() << "�� �����߽��ϴ�." << endl;
}

void ShopUI::printSellltem(Item* item)
{
	cout << "\n" << item->getName() << "�� �Ǹ��߽��ϴ�.";
}

void ShopUI::printWrongInput()
{
	cout << "�߸��� �Է��Դϴ�.\n" << endl;
}

void ShopUI::printScore(vector<int>& numbers)
{
	cout << " " << numbers.back() << " ���Խ��ϴ�." << endl;

	cout << "����:";

	for (int num : numbers)
	{
		cout << " " << num;
	}

	cout << "\n" << endl;
}

void ShopUI::printDisplaySum(vector<int>& numbers, int sum)
{
	cout << "����: ";

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

	// 1��
	if (score > 10000)
	{
		cout << "�� ����� 1�� ��÷" << endl;

		return;
	}

	// 2��
	if (score > 1000)
	{
		cout << "2�� ��÷" << endl;
		cout << "���ݷ��� " << 10 * multiple << "�� �����մϴ�." << endl;

		return;
	}

	// 3��
	if (score > 100)
	{
		cout << "3�� ��÷";

		return;
	}

	// 4��
	if (score > 50)
	{
		cout << "4�� ��÷";

		return;
	}

	// ��
	cout << "��! >o< ���� ��ȸ��~" << endl;
}

void ShopUI::printUnluckyNumber()
{
	cout << "\n��Ű�ѹ� UnU" << endl;
	cout << "�ɷ�ġ�� �ʱ�ȭ �Ǿ����ϴ�..." << endl;
}
