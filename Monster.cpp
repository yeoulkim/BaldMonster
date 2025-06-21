#include "Monster.h"

Monster::Monster(int Hp, int Atk)
    : Health(Hp), Attack(Atk)
{
}

int Monster::GetHealth() const
{
    return Health;
}

int Monster::GetAttack() const
{
    return Attack;
}

void Monster::TakeDamage(int Dmg)
{
    Health -= Dmg;
    if (Health < 0)
        Health = 0;
}
