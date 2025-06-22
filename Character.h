#pragma once
#include <string>

class Character
{
private:
    std::string Name;
    int Level;
    int Health;
    int MaxHealth;
    int Attack;
    int Experience;
    int Gold;

public:
    Character(std::string Name, int Level, int Health, int Attack, int Experience, int Gold);
    Character(std::string Name);

    std::string GetName() const;
    int GetLevel() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetExperience() const;
    int GetGold() const;

    void SetGold(int NewGold);
    void SetLevel(int Level);
    void SetHealth(int Health);
    void SetAttack(int Attack);
    void SetExperience(int Experience);

    void TakeDamage(int Damage);
};
