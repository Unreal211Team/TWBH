#include "Character.h"
#include "Item.h"
#include "BuffManager.h"
#include <iostream>
#include "PowerStrike.h"
#include "MagicClaw.h"


Character::Character()
{
	mana = 100; 
	maxMana = 100;
	level = 1;
	health = maxHealth = 200;
	attack = 30;
	experience = 0;
	maxExperience = 100;
	gold = 300;				// Gamble �ÿ� �ڱ�
	bIsAlive = true;
  
	skills.push_back(new PowerStrike());
	skills.push_back(new MagicClaw());
}

Character& Character::getInstance()
{
	static Character character;
	return character;
}

void Character::displayStatus() const
{
	cout << "\n";
	cout << " --- status ---" << "\n" << "\n";
	cout << " �̸� : " << name << "\n";
	cout << " Lv." << level << "\n";
	cout << " Exp	  (" << experience << "/" << maxExperience << ")" << "\n";
	cout << " HP	  (" << health << "/" << maxHealth << ")\n";
	cout << " ���ݷ�	  " << attack << "\n";
	BuffManager* manager = BuffManager::getInstance();
	if (manager->ActiveBuffsCheck())
	{
		manager->displayBuffs();
	}
	cout << " --- ----- ---\n\n";
}

string Character::getName() const
{
	return name;
}

void Character::setName(const string& name)
{
	this->name = name;
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

int Character::getMana() const
{
	return mana;
}

int Character::getMaxMana() const
{
	return maxMana;
}

void Character::setMana(int mana)
{
	this->mana = max(mana, 0);
}

void Character::setMaxMana(int maxMana)
{
	this->maxMana = maxMana;
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

	//�����ѷ���
	maxMana += 10;

	//����ȸ��
	mana = maxMana;


	cout << getName() << "��(��) ������! ";
	cout << "Lv." << getLevel() << endl;
}

void Character::addItem(Item* item)
{
	inventory.push_back(item);
	cout << getName() << "�� \"";
	cout << item->getName() << "\"�� ȹ���߽��ϴ�." << endl;
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

//���� ����
void Character::resetAttackBuff()
{
	attack -= 10;
}

bool Character::isDead()
{
	if (health <= 0)
	{
		bIsAlive = false;
		cout << getName() << "��(��) ����߽��ϴ�. ���� ����!" << endl;

	}
	return bIsAlive;
}

Character::~Character()
{
  
	// �޸� ����
	for (Skill* skill : skills)
	{	
		delete skill;
	}
	skills.clear();
  
	for (Item* item : inventory)
	{
		delete item;  // �����ۿ� ���� �޸� ����
	}
	inventory.clear();  // ���� ����
}