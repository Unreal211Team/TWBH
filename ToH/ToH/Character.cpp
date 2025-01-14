#include "Character.h"
#include "Item.h"
#include <iostream>


Character* Character::instance = nullptr;

Character::Character(string name) : name(name)
{
	level = 1;
	health = maxHealth = 200;
	attack = 30;
	experience = 0;
	maxExperience = 100;
	gold = 300;				// Gamble �ÿ� �ڱ�
}

Character* Character::getInstance(const string& name)
{
	if (instance == nullptr)
	{
		instance = new Character(name);
	}

	return instance;
}

void Character::displayStatus() const
{
	cout << " --- status ---" << "\n";
	cout << " �̸� : " << name << "\n";
	cout << " Lv." << level << "	(" << experience << "/" << maxExperience << ")" << "\n";
	cout << " HP	(" << health << "/" << maxHealth << ")\n";
	cout << " ���ݷ�	" << attack << "\n";
}

string Character::getName() const
{
	return name;
}

int Character::getLevel() const
{
	return level;
}

void Character::setLevel(int level)
{
	this->level = level;
}

int Character::getHealth() const
{
	return health;
}

void Character::setHealth(int health)
{
	this->health = max(health, 0);
}

int Character::getMaxHealth() const
{
	return maxHealth;
}

void Character::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

int Character::getAttack() const
{
	return attack;
}

void Character::setAttack(int attack)
{
	this->attack = attack;
}

int Character::getExperience() const
{
	return experience;
}

void Character::setExperience(int experience)
{
	this->experience = experience;
}

int Character::getMaxExperience() const
{
	return maxExperience;
}

void Character::setMaxExperience(int maxExperience)
{
	this->maxExperience = maxExperience;
}

void Character::addExperience(int experience)
{
	this->experience += experience;
}

int Character::getGold() const
{
	return gold;
}

void Character::addGold(int gold)
{
	this->gold += gold;
}

void Character::takeDamage(int damage)
{
	setHealth(this->health - damage);
}

vector<Item*>& Character::getInventory()
{
	return inventory;
}

bool Character::IsLevelUp() const
{
	return experience >= maxExperience;
}

void Character::levelUp()
{
	// ����ġ ����
	experience -= maxExperience;

	// �䱸 ����ġ ����
	maxExperience *= 1.2;
	maxExperience = (maxExperience / 10) * 10;  // 10�� ����� ����

	// ������
	++level;

	// ü�¾�
	maxHealth += 20;

	// ����ȸ��
	health = maxHealth;

	// ���ݾ�
	attack += 5;
}

void Character::addItem(Item* item)
{
	inventory.push_back(item);
}

void Character::useItem(int index)
{
	// ��� ������ ��� �Ұ�
	if (!inventory[index]->canUse())
	{
		cout << "��� �Ұ����� �������Դϴ�." << endl;
		return;
	}

	cout << inventory[index]->getName() << "�� ����մϴ�." << endl;

	inventory[index]->use(this);

	// �޸� ���� �� erase
	delete inventory[index];

	inventory.erase(inventory.begin() + index);
}

Character::~Character()
{
	// �޸� ����
	for (Item* item : inventory)
	{
		delete item;  // �����ۿ� ���� �޸� ����
	}
	inventory.clear();  // ���� ����
}