#pragma once

class Monster {
protected:
    int health;
    int attack;

public:
    Monster(int hp, int atk);
    virtual ~Monster() {}

    int getHealth() const;
    int getAttack() const;
    void takeDamage(int dmg);
};

