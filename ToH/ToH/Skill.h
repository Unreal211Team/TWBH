#pragma once
#include <string>
#include <iostream>

using namespace std;

class Character;

class Skill 
{
protected:
    string name;   
    int mana;           
    double multiplier;  

public:
    Skill(const string& name, int mana, double multiplier)
        : name(name), mana(mana), multiplier(multiplier) {
    }

    virtual ~Skill() = default;

    const string& getName() const { return name; }
    int getMana() const { return mana; }

    virtual void use(Character* player, Character* target) = 0;
};
