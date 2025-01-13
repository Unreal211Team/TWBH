#pragma once

#include "Item.h"

class OrcDropItem : public Item
{
private:
	const std::string name;
	const bool canUsing;
	const int price;
};