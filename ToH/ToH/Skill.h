#pragma once
#include <string>
#include <iostream>

using namespace std;

class Character;

class Skill 
{
public:

    virtual ~Skill() = default;

    virtual const string& getName() const = 0;
    virtual int getMana() const = 0;

    virtual void use(Character* player, Monster* target) = 0;
};
