#pragma once
#include <string>
#include "Monster.h"

using namespace std;

class EliteMonster:public Monster
{
protected:
	string asciiArt;
private:
	Monster* originalMonster; //���� ����
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
	void displayArt() const override
	{
		cout << "            _/\\_/\\_" << endl;    
		cout << "           /       \\" << endl;
		cout << "          /  Elite  \\" << endl;
		cout << "           \\_______/" << endl;
		originalMonster->displayArt();
	}
	
};

