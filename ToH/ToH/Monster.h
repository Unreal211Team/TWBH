#pragma once

#include <string>
#include "Item.h"
#include <iostream>

using namespace std;
class Monster
{
protected:
	string asciiArt;

public:
	virtual string getName() const = 0;
	virtual int getHealth() const = 0;
	virtual	int getAttack() const = 0;
	virtual void takeDamage(int damage) = 0;
	virtual	Item* dropItem() const = 0;

	virtual void displayArt() const
	{
		cout << asciiArt << endl;

	}
	virtual string getAsciiArt() const
	{
		return asciiArt;
	}
};