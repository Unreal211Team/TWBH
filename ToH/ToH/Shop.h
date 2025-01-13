#pragma once

#include <vector>
#include "Item.h"

class Shop
{
private:
	static Shop* instance;
	std::vector<Item*> avaliableItems;
};