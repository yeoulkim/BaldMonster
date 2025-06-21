#include "Monster.h"

Monster::Monster(int hp, int atk) : health(hp), attack(atk) {}

int Monster::getHealth() const { return health; }
int Monster::getAttack() const { return attack; }

void Monster::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}
