#pragma once

class Monster
{
protected:
    int Health;
    int Attack;

public:
    Monster(int Hp, int Atk);
    virtual ~Monster() {}

    int GetHealth() const;
    int GetAttack() const;
    void TakeDamage(int Dmg);
};
