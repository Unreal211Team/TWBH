#pragma once
#include <string>

using namespace std;

class IObserver
{
public:
	
	virtual ~IObserver() = default;

	// 몬스터 이벤트 
	virtual void OnMonsterEvent(const string& monsterName, const string& eventType) = 0;

	// 아이템 이벤트
	virtual void OnItemEvent(const string& itemName, const string& eventType, int recoveredHealth = 0, int recoveredMana = 0) = 0;

	// 전투 관련 이벤트
	virtual void OnBattleEvent(const string& skillName, const string& eventType, int damage) = 0;

	// 골드 관련 이벤트
	virtual void OnGoldEvent(const string& eventType, int gold) = 0;

};
