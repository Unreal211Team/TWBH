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
	int getValidatedInput(const string& prompt, int minValue, int maxValue);
	void displayInventory(Character* player);
	void useItemFromInventory(Character* player);

private:
	int experience = 50;// ���� ���� ����ġ 50
	int itemDrop = 30;	// ������ ��� Ȯ�� 30��
	BattleUi battleui;
	ActingMonster actingMonster;
};