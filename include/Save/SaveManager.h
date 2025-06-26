//
// Created by suaio on 2025-06-26.
//

#pragma once
#include <string>
#include "Character.h"

class SaveManager {
    public:
        // 게임 내용 저장
        static bool SaveGame(Character *player, const std::string &fileName);
        // 게임 내용 불러오기
        static bool LoadGame( Character* player, const std::string& fileName);
};
