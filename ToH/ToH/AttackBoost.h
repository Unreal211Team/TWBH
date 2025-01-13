#pragma once

#include "Item.h"

class AttackBoost : public Item
{
private:
	const std::string name;
	const bool canUsing;		// 아이템 사용 가능 여부
	const int price;
	const int attackIncrease;	// 공격력 증가량
};