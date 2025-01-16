#include "Report.h"

PlayReport* PlayReport::Instance = nullptr;

void PlayReport::OnMonsterEvent(const string& monsterName, const string& eventType)
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

void PlayReport::OnItemEvent(const string& itemName, const string& eventType, int recoveredHealth, int recoveredMana)
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

void PlayReport::OnBattleEvent(const string& attackName, const string& eventType, int damage)
{
    if (eventType == "BasicAttack")
    {
        AttackCountByType[attackName]++;
        TotalBasicAttackDamage += damage;
    }
    else if (eventType == "SkillAttack")
    {
        AttackCountByType[attackName]++;
        TotalSkillAttackDamage += damage;
    }

    TotalDamageDealt += damage;
}

void PlayReport::OnGoldEvent(const string& eventType, int gold)
{
    if (eventType == "EarnGold")
    {
        TotalGoldEarned += gold;
    }
    else if (eventType == "SpendGold")
    {
        TotalGoldSpent += gold;
    }
}

void PlayReport::GenerateMonsterReport() const
{
    cout << "\n == == == Monster Statistics == == ==\n";
    PrintMap("  Spawn Monster Count  ", SpawnMonsterCount);
    PrintMap("  Kill Monster Count  ", KillMonsterCount);
}

void PlayReport::GenerateItemReport() const
{
    cout << "\n == == ==  Item Statistics  == == == \n";
    PrintMap("\n -- -- --  Acquired Items  -- -- -- \n", AcquiredItems);
    PrintMap("\n -- -- --    Used Items    -- -- -- \n", UsedItems);
}

void PlayReport::GenerateBattleReport() const
{
    cout << "\n == == == Battle Statistics == == == \n";
    PrintMap("\n -- -- --   Attack Count   -- -- -- \n", AttackCountByType);
    cout << "  Total Skill Attack Damage : " << TotalSkillAttackDamage << "\n";
    cout << "  Total Basic Attack Damage : " << TotalBasicAttackDamage << "\n";
    cout << "  Total Attack Damage : " << TotalDamageDealt << "\n";
}

void PlayReport::GenerateGoldReport() const
{
    cout << "\n == == ==  Gold Statistics  == == == \n";
    cout << "  Total Gold Earned : " << TotalGoldEarned << "\n";
    cout << "  Total Gold Spent : " << TotalGoldSpent << "\n";
    cout << "  Curren Gold : " << CurrentGold() << "\n";
}

int PlayReport::CurrentGold() const
{
    return TotalGoldEarned - TotalGoldSpent;
}


// 무엇에 대한 출력값인지, 해당 맵
void PlayReport::PrintMap(const string& Title, const map<string, int>& Data) const
{
    cout << "\n" << Title << "\n";

    for (map<string, int>::const_iterator it = Data.begin(); it != Data.end(); ++it)
    {
        cout << "  " << it->first << " : " << it->second << "\n";
    }

}


void PlayReport::GenerateReport() const
{
    cout << "\n == == == == Game Report == == == ==\n";


    GenerateMonsterReport();


    GenerateBattleReport();


    GenerateItemReport();


    GenerateGoldReport();
}



