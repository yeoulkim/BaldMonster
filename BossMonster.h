#pragma once
#include "MonsterBase.h"

class BossMonster : public MonsterBase
{
public:
    BossMonster(int Level);

    std::string GetName() const override;
    std::string GetRandomLine() override;
    int GetHealth() const override;
    int GetAttack() const override;
    void TakeDamage(int Damage) override;

private:
    std::string Name;
    int Health;
    int Attack;
    std::vector<std::string> Lines;
};