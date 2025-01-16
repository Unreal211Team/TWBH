#pragma once
#include <string>

using namespace std;

class IObserver
{
public:
	
	virtual ~IObserver() = default;

	// ���� �̺�Ʈ 
	virtual void OnMonsterEvent(const string& monsterName, const string& eventType) = 0;

	// ������ �̺�Ʈ
	virtual void OnItemEvent(const string& itemName, const string& eventType, int recoveredHealth = 0, int recoveredMana = 0) = 0;

	// ���� ���� �̺�Ʈ
	virtual void OnBattleEvent(const string& skillName, const string& eventType, int damage) = 0;

	// ��� ���� �̺�Ʈ
	virtual void OnGoldEvent(const string& eventType, int gold) = 0;

};
