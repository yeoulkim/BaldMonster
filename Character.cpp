#include "Character.h"

Character::Character(std::string Name, int Level, int Health, int Attack, int Experience)
    : Name(Name), Level(Level), Health(Health), MaxHealth(Health), Attack(Attack), Experience(Experience)
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
    Health -= Damage;
    if (Health < 0) Health = 0;
}
