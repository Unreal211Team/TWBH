#pragma once
#include "ActingMonster.h"
#include "BattleUi.h"
#include "BuffManager.h"
#include "PowerStrike.h"
#include "MagicClaw.h"

class Battle
{
public:
	Battle();
	bool doBattle();
	bool doFight(Monster& monster);
	int getValidatedInput(const string& prompt, int minValue, int maxValue);
	void displayInventory(Character* player);
	void useItemFromInventory(Character* player);

private:
	int experience = 50;// 몬스터 고정 경험치 50
	int itemDropRate = 30;	// 아이템 드롭 확률 30퍼
	int randomGold = 10;
	int randomInt(int start, int end);

	bool attackChoice(Monster& monster);

	void getReward(Monster& monster);

	BuffManager* manager = BuffManager::getInstance();
	Character& player = Character::getInstance();

	BattleUi battleUi;
	ActingMonster actingMonster;
};