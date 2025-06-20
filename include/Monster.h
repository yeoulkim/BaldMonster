#ifndef MONSTER_H
#define MONSTER_H
#include <string>
#include <memory>
#include "Item.h"

// 몬스터 클래스
class Monster {
protected:
    std::string name;
    int health;
    int attack;
public:
    Monster(std::string n,int h,int a);
    virtual ~Monster() = default;
    const std::string& getName() const;
    int getHealth() const;
    int getAttack() const;
    void takeDamage(int dmg);
    virtual std::unique_ptr<Item> dropItem();
};

// 노랭이
class Yellow : public Monster {
public:
    Yellow(int lvl);
};

// 하양이
class White : public Monster {
public:
    White(int lvl);
};

// 초록이
class Green : public Monster {
public:
    Green(int lvl);
};

// 파랭이
class Blue : public Monster {
public:
    Blue(int lvl);
};

// 빨갱이
class Pink : public Monster {
public:
    Pink(int lvl);
};

// 깜댕이
class Black : public Monster {
public:
    Black(int lvl);
};

#endif