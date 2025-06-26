//
// Created by suaio on 2025-06-24.
//
#include "Monster/BossMonster.h"
#include "Monster/MonsterBase.h"
#include <iostream>

// 보스 몬스터 생성자
BossMonster::BossMonster(MonsterDefinition def, int level)
    : MonsterBase(std::move(def), level) {}

// 턴 활용
void BossMonster::GetTurn() {
    if (CurrentMP >= 20) {
        std::cout << GetName() << " 탈모-빔!\n";
        CurrentMP -= 20;
    } else {
        MonsterBase::GetTurn();
    }
}
