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
	int experience = 50;// ���� ���� ����ġ 50
	int itemDropRate = 30;	// ������ ��� Ȯ�� 30��
	int randomGold = 10;
	int randomInt(int start, int end);

	bool attackChoice(Monster& monster);

	void getReward(Monster& monster);

	BuffManager* manager = BuffManager::getInstance();
	Character& player = Character::getInstance();

	BattleUi battleUi;
	ActingMonster actingMonster;
};