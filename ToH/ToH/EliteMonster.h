#pragma once
#include <string>
#include "Monster.h"

using namespace std;
#include <sstream>
class EliteMonster:public Monster
{
protected:
	string asciiArt;
private:
	Monster* originalMonster; //원래 몬스터
	string name;	//이름
	int health;		//체력
	int attack;		//공격

public:
	EliteMonster(Monster* monster);
	EliteMonster(shared_ptr<Monster>& monster);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
	void displayArt() const override
	{
		cout << asciiArt;
	}
	
};

