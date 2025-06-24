#pragma once
#include<iostream>
#include<string>
#include "Character.h"
#include "MonsterBase.h"
class BattleSystem
{
public:
    static void StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience);
};