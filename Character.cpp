#include "Character.h"

Character::Character(std::string name, int level, int health, int attack, int experience)
    : name(name), level(level), health(health), maxHealth(health), attack(attack), experience(experience) {
}

std::string Character::getName() const { return name; }
int Character::getLevel() const { return level; }
int Character::getHealth() const { return health; }
int Character::getMaxHealth() const { return maxHealth; }
int Character::getAttack() const { return attack; }
int Character::getExperience() const { return experience; }

void Character::setLevel(int l) { level = l; }
void Character::setHealth(int h) { health = h; }
void Character::setAttack(int a) { attack = a; }
void Character::setExperience(int e) { experience = e; }

void Character::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}
