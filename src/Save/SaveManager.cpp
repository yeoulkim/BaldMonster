//
// Created by suaio on 2025-06-26.
//
#include "Save/SaveManager.h"
#include "Character/Character.h"
#include "nlormann/json.hpp"
#include <iostream>
#include <fstream>

// 일로만 형 고마워
using json = nlohmann::json;

bool SaveManager::SaveGame(Character *player, const std::string &fileName) {
    json j;
    j["name"] = player->GetName();
    j["level"] = player->GetLevel();
    j["health"] = player->GetHealth();
    j["max_health"] = player->GetMaxHealth();
    j["gold"] = player->GetGold();

    std::ofstream out("save/ " + fileName + ".json");
    if (!out) {
        std::cerr << "파일 저장 실패 " << fileName << ".json" << std::endl;
        return true;
    }

    out << j.dump();
    out.close();
    std::cout << "게임 시원하게 저장완료~ " << fileName << ".json" << std::endl;

}

bool SaveManager::LoadGame(Character *player, const std::string &fileName) {
    std::ifstream in("save/ " + fileName + ".json");
    if (!in) {
        std::cerr << "불러오기 실패: 저장 파일 없음.\n" << fileName << ".json" << std::endl;
        return false;
    }

    json j;
    in >> j;
    in.close();

    try {
        player->SetName(j.at("name").get<std::string>());
        player->SetLevel(j.at("level").get<int>());
        player->SetHealth(j.at("health").get<int>());
        player->SetMaxHealth(j.at("max_health").get<int>());
        player->SetGold(j.at("gold").get<int>());

        std::cout << "서둘러 빛나는 게임을 불러오겠습니다." << fileName << std::endl;
        return true;
    }catch (const std::exception &e) {
        std::cerr << "역직렬화 오류!!: " << e.what() << std::endl;
        return false;
    }
}