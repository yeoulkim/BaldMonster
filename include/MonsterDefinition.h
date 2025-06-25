//
// Created by suaio on 2025-06-24.
//

#pragma once
#include <string>
#include <vector>
#include "DropEntry.h"

// 몬스터 정의 구조체
struct MonsterDefinition {
    std::string name; // 몬스터 이름
    int HP, MP, Attack; // 몬스터 HP / MP / 공격력 (기본)
    std::vector<std::string> lines; // 몬스터 대사
    std::vector<DropEntry> DropTable; // 드랍 아이템
};
