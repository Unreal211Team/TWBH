#pragma once
#include "Character.h"

class CharacterUI
{
public:
    static void displayStatus(const Character* character);
    static void displayExperienceGain(const Character* character, int experience);
    static void displayGoldGain(const Character* character, int gold);
    static void displayDamageTaken(const Character* character, int damage);
    static void displayLevelUp(const Character* character);
    static void displayItemGain(const Character* character, const string& itemName);
    static void displayItemUse(const Character* character, const string& itemName);
    static void displayItemCannotUse();
    static void displayDeath(const Character* character);
    static void displayEscape(const Character& character);
};
