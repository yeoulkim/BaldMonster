#pragma once
#include <string>

class Character {
private:
    std::string name;
    int level;
    int health;
    int maxHealth;
    int attack;
    int experience;

public:
    Character(std::string name, int level, int health, int attack, int experience);

    std::string getName() const;
    int getLevel() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttack() const;
    int getExperience() const;

    void setLevel(int l);
    void setHealth(int h);
    void setAttack(int a);
    void setExperience(int e);

    void takeDamage(int damage);
};
