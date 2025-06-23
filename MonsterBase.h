#pragma once
#include <string>
#include <vector>

class MonsterBase
{
public:
    virtual ~MonsterBase() {}

    virtual std::string GetName() const = 0;
    virtual std::string GetRandomLine() = 0;
    virtual int GetHealth() const = 0;
    virtual int GetAttack() const = 0;
    virtual void TakeDamage(int Damage) = 0;
};
