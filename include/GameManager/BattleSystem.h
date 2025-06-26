#pragma once
#include<iostream>
#include<string>
#include "Monster/MonsterBase.h"

// 전투관리 열거 추가
enum class PlayAction {Attack = 1, UseItem = 2, Run = 3};

class BattleSystem
{
public:
    void DungeonMenu(Character* player);

    static MonsterBase * SummonRandomMonster(int GetLevel);

    static void StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience);
};