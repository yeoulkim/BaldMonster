#include "Character.h"
#include <iostream>
#include <ctime> // for rand() and srand()
#include <cstdlib>

Character::Character(std::string Name, int Level, int Health, int Attack, int Experience, int Gold)
    : Name(Name),
    Level(Level),
    Health(Health),
    MaxHealth(Health),
    Attack(Attack),
    Experience(Experience),
    Gold(Gold)
{
}


std::string Character::GetName() const { return Name; }
int Character::GetLevel() const { return Level; }
int Character::GetHealth() const { return Health; }
int Character::GetMaxHealth() const { return MaxHealth; }
int Character::GetAttack() const { return Attack; }
int Character::GetExperience() const { return Experience; }

void Character::SetLevel(int NewLevel) { Level = NewLevel; }
void Character::SetHealth(int NewHealth) { Health = NewHealth; }
void Character::SetAttack(int NewAttack) { Attack = NewAttack; }
void Character::SetExperience(int NewExp) { Experience = NewExp; }

void Character::TakeDamage(int Damage)
{
    if (rand() % 5 == 0)  // 20% 확률 회피
    {
        std::cout << "공격을 회피했습니다!\n";
        return;
    }

    Health -= Damage;
    if (Health < 0) Health = 0;
}


int Character::GetGold() const
{
    return Gold;
}

void Character::SetGold(int NewGold)
{
    Gold = NewGold;
}

Character::Character(std::string Name)
    : Name(Name), Level(1), Health(20), MaxHealth(20), Attack(30), Experience(0), Gold(0)
{
}
