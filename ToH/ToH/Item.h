#pragma once

#include <string>

class Character;

class Item
{
public:
	virtual	std::string getName() const = 0;
	virtual bool canUse() const = 0;
	virtual	void use(Character* character) const = 0;
	virtual	int getPrice() const = 0;
	virtual ~Item() = default;
};