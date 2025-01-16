#pragma once
#include <sstream>
#include "Monster.h"
#include "Character.h"

class BattleUi
{
public:
	void spawnMonster(const Monster& monster) const;

	void displayMonsterStats(const Monster& monster) const;

	void selectBattleOptions(const Monster& monster) const;

	void showCurrentManaAndAttack(const Monster& monster) const;

	void displayAttackMessage(const Monster& monster) const;

	void displayHitMessage(const Monster& monster) const;

	void displayRewardMessage(const Monster& monster, const int exp, const int gold, Item* takeItem = nullptr) const;

	void monsterDisplay(const Monster& monster) const;

	int getValidatedInput(const string& prompt, int minValue, int maxValue);

	void displayWrongInput() const;

	void manaAlert() const;
	void displayShortStatus() const;
	void displayClear() const;
	void exitmenu() const;
};