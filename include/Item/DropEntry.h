//
// Created by suaio on 2025-06-24.
//

#pragma once
#include <string>

// 몬스터 드랍 구조체 (단순 데이터 묶음)
struct DropEntry {
    std::string ItemName; // 아이템 이름
    double DropRate; // 드랍 확율
};
