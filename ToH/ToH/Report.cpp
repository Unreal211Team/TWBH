#include "Report.h"

// 무엇에 대한 출력값인지, 해당 맵
void Report::PrintMap(const string& Title, const map<string, int>& Data) const 
{
    cout << "\n" << Title << "\n";

    for (map<string, int>::const_iterator it = Data.begin(); it != Data.end(); ++it) 
    {
        cout << "  " << it->first << ": " << it->second << "\n";
    }
}

void Report::OnMonsterEvent(const string& monsterName, const string& eventType)
{
    if (eventType == "spawn")
    {
        SpawnMonsterCount[monsterName]++;
    }
    else if(eventType == "kill")
    {
        KillMonsterCount[monsterName]++;
    }
}

void Report::OnItemEvent(const string& itemName, const string& eventType, int recoveredHealth, int recoveredMana)
{
    if (eventType == "use")
    {
        UsedItems[itemName]++;
        TotalRecoveredHealth += recoveredHealth;
        TotalRecoveredMana += recoveredMana;
    }
    else if (eventType == "Acquire")
    {
        AcquiredItems[itemName]++;
    }
}

void Report::OnBattleEvent(const string& skillName, const string& eventType, int damage)
{
    if (eventType == "BasicAttack")
    {
        BasicAttackCount++;
        TotalBasicAttackDamage += damage;
    }
    else if (eventType == "SkillAttack")
    {
        SkillAttackCount[skillName]++;
        TotalSkillAttackDamage += damage;
    }

    TotalDamageDealt += damage;
}

void Report::GenerateReport() const
{


}



