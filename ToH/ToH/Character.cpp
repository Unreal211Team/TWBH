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
	gold = 300;				// Gamble 시연 자금
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
	cout << " 이름 : " << name << "\n";
	cout << " Lv." << level << "\n";
	cout << " Exp	  (" << experience << "/" << maxExperience << ")" << "\n";
	cout << " HP	  (" << health << "/" << maxHealth << ")\n";
	cout << " 공격력	  " << attack << "\n";
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

	// 경험치 감소
	experience -= maxExperience;

	// 요구 경험치 증가
	maxExperience *= 1.2;
	maxExperience = (maxExperience / 10) * 10;  // 10의 배수로 설정

	// 레벨업
	++level;

	// 체력업
	maxHealth += 20;

	// 완전회복
	health = maxHealth;

	// 공격업
	attack += 5;

	//마나총량업
	maxMana += 10;

	//마나회복
	mana = maxMana;


	cout << getName() << "이(가) 레벨업! ";
	cout << "Lv." << getLevel() << endl;
}

void Character::addItem(Item* item)
{
	inventory.push_back(item);
	cout << getName() << "가 \"";
	cout << item->getName() << "\"을 획득했습니다." << endl;
}

void Character::useItem(int index)
{
	// 재료 아이템 사용 불가
	if (!inventory[index]->canUse())
	{
		cout << "사용 불가능한 아이템입니다." << endl;
		return;
	}

	cout << inventory[index]->getName() << "을 사용합니다." << endl;

	inventory[index]->use(this);

	// 메모리 해제 후 erase
	delete inventory[index];

	inventory.erase(inventory.begin() + index);
}

//버프 종료
void Character::resetAttackBuff()
{
	attack -= 10;
}

bool Character::isDead()
{
	if (health <= 0)
	{
		bIsAlive = false;
		cout << getName() << "이(가) 사망했습니다. 게임 오버!" << endl;

	}
	return bIsAlive;
}

Character::~Character()
{
  
	// 메모리 해제
	for (Skill* skill : skills)
	{	
		delete skill;
	}
	skills.clear();
  
	for (Item* item : inventory)
	{
		delete item;  // 아이템에 대한 메모리 해제
	}
	inventory.clear();  // 벡터 비우기
}