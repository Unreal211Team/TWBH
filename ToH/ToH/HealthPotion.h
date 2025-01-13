#pragma once

#include "Item.h"

class HealthPotion : public Item
{
private:
	const std::string name;
	const bool canUsing;		// ������ ��� ���� ����
	const int price;
	const int healthRestore;	// ü�� ȸ����
};