#include "Character.h"
#include "Item.h"
#include "BuffManager.h"
#include <iostream>
#include "PowerStrike.h"
#include "MagicClaw.h"
#include "CharacterUI.h"


Character* Character::instance = nullptr;


Character::Character(string name) : name(name)
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
	CharacterUI::displayStatus(this);
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
	CharacterUI::displayExperienceGain(this, experience);
}

int Character::getGold() const
{
	return gold;
}

void Character::addGold(int gold)
{
	this->gold += gold;
	CharacterUI::displayGoldGain(this, gold);
	
}

void Character::takeDamage(int damage)
{
	setHealth(this->health - damage);

	CharacterUI::displayDamageTaken(this, damage);
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


	CharacterUI::displayLevelUp(this);
}

void Character::addItem(Item* item)
{
	inventory.push_back(item);
	CharacterUI::displayItemGain(this, item->getName());
}

void Character::useItem(int index)
{
	// ��� ������ ��� �Ұ�
	if (!inventory[index]->canUse())
	{
		CharacterUI::displayItemCannotUse();
		return;
	}

	CharacterUI::displayItemUse(this, inventory[index]->getName());

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
		CharacterUI::displayDeath(this);

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