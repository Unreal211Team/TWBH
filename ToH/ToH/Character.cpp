#include "Character.h"
#include "Item.h"
#include <iostream>


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
  gold = 300;				// Gamble 시연 자금
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
	cout << " --- status ---" << "\n";
	cout << " 이름 : " << name << "\n";
	cout << " Lv." << level << "\n";
	cout << " Exp	  (" << experience << "/" << maxExperience << ")" << "\n";
	cout << " HP	  (" << health << "/" << maxHealth << ")\n";
	cout << " 공격력	  " << attack << "\n";
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
	cout << getName() << "가 ";
	cout << experience << " Exp 를 획득하였습니다. \n";
}

int Character::getGold() const
{
	return gold;
}

void Character::addGold(int gold)
{
	this->gold += gold;

	cout << getName() << "가 ";
	if (gold > 0)
	{
		cout << gold << " 골드를 획득했습니다. \n";
	}
	else
	{
		cout << (-1)*gold << " 골드를 소모했습니다. \n";
	}

}

void Character::takeDamage(int damage)
{
	setHealth(this->health - damage);

	cout << getName() << "을(를) 공격합니다! ";
	cout << getName() << " 체력: " << getHealth() << endl;
}



vector<Item*>& Character::getInventory()
{
	return inventory;
}

bool Character::IsLevelUp() const
{
	return experience >= maxExperience;
}

int Character::getMana() const
{
	return mana;
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
  skill.clear();
  
	for (Item* item : inventory)
	{
		delete item;  // 아이템에 대한 메모리 해제
	}
	inventory.clear();  // 벡터 비우기
}