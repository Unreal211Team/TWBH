#pragma once
#include <iostream>
#include <map>
#include <string>
#include "IObserver.h"

#define REPORT PlayReport::GetInstance()

using namespace std;

class PlayReport : public IObserver
{
private:
    static PlayReport* Instance;

    // 싱글톤 생성자
    PlayReport() = default;

public:
    static PlayReport* GetInstance()
    {
        if (Instance == nullptr)
        {
            Instance = new PlayReport();
        }
        return Instance;
    }


private:

    // 몬스터 통계
    map<string, int> SpawnMonsterCount;
    map<string, int> KillMonsterCount;

    // 아이템 통계
    map<string, int> UsedItems;
    map<string, int> AcquiredItems;

    // 회복 아이템 사용 시 회복된 총량
    map<string, int> RecoveredCount;
    int TotalRecoveredHealth = 0;
    int TotalRecoveredMana = 0;

    // 골드 통계
    int TotalGoldEarned = 0;
    int TotalGoldSpent = 0;

    // 전투 통계
    map<string, int> AttackCountByType;
    int BasicAttackCount = 0;
    int TotalSkillAttackDamage = 0;
    int TotalBasicAttackDamage = 0;
    int TotalDamageDealt = 0;

    // 헬퍼 함수
    void PrintMap(const string& title, const map<string, int>& data) const;

public:

    // 기록 관련 함수
    void OnMonsterEvent(const string& monsterName, const string& eventType) override;
    void OnItemEvent(const string& itemName, const string& eventType, int recoveredHealth = 0, int recoveredMana = 0) override;
    void OnBattleEvent(const string& skillName, const string& eventType, int damage) override;
    void OnGoldEvent(const string& eventType, int gold) override;


    // 출력 관련 함수
    void GenerateMonsterReport() const;
    void GenerateItemReport() const;
    void GenerateBattleReport() const;
    void GenerateGoldReport() const;

    
    int CurrentGold() const;


    // 전체 데이터 출력
    void GenerateReport() const;

};