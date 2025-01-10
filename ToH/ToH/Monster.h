#pragma once

#include <string>

using namespace std;

class Monster
{
public:
	virtual string	getName() const = 0;
	virtual int		getHealth() const = 0;
	virtual	int		getAttack() const = 0;
	virtual void	takeDamage(int damage) = 0;
};