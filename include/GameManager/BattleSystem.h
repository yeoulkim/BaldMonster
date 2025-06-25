#pragma once
#include<iostream>
#include<string>
#include "../../include/Character/Character.h"
#include "../../include/Monster/MonsterBase.h"
class BattleSystem
{
public:
    static void StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience);
};