#pragma once

#include "Item.h"

class AttackBoost : public Item
{
private:
	const std::string name;
	const bool canUsing;		// ������ ��� ���� ����
	const int price;
	const int attackIncrease;	// ���ݷ� ������
};