#pragma once

#include "Item.h"

class GoblinDropItem : public Item
{
private:
	const std::string name;
	const bool canUsing;	// ������ ��� ���� ����
	const int price;
};