#pragma once
#include <string>
#include "Monster.h"

using namespace std;

class EliteMonster:public Monster
{
private:
	string name;	//�̸�
	int health;		//ü��
	int attack;		//����

public:
	EliteMonster(Monster* monster);
	string getName() const override;
	int getHealth() const override;
	int getAttack() const override;
	void takeDamage(int damage) override;
	Item* dropItem() const override;
};

