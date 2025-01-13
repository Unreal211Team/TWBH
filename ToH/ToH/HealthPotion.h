#pragma once

#include "Item.h"

class HealthPotion : public Item
{
private:
	const std::string name;
	const bool canUsing;		// 아이템 사용 가능 여부
	const int price;
	const int healthRestore;	// 체력 회복량
};