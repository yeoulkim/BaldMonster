#pragma once

#include "Character.h"
#include "MonsterBase.h"
class BattleSystem
{
public:
    static void StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience);
};