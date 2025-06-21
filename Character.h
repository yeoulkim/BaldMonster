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

public:
    Character(std::string Name, int Level, int Health, int Attack, int Experience);

    std::string GetName() const;
    int GetLevel() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetExperience() const;

    void SetLevel(int Level);
    void SetHealth(int Health);
    void SetAttack(int Attack);
    void SetExperience(int Experience);

    void TakeDamage(int Damage);
};
