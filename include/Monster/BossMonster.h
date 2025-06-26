//
// Created by suaio on 2025-06-24.
//
#pragma once
#include "MonsterBase.h"

class BossMonster : public MonsterBase {
public:
    BossMonster(MonsterDefinition def, int level);
    void GetTurn() override;
};
