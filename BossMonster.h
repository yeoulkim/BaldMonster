#pragma once
#include "Monster.h"

class BossMonster : public Monster
{
public:
    BossMonster(std::string Name, int Health, int Attack);
};
