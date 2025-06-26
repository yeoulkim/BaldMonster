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
namespace fs = std::filesystem;

// 저장될 경로 생성
static fs::path slotPath(const std::string& slot) {
    return fs::path("save") / (slot + ".json");
}

// 게임 데이터 직렬화 저장
bool SaveManager::SaveGame(Character *player, const std::string& slot) {

    try {
        // save 파일 생성
        fs::create_directories("save");

        json j;
        j["name"] = player->GetName();
        j["max_health"] = player->GetMaxHealth();
        j["health"] = player->GetHealth();
        j["level"] = player->GetLevel();
        j["attack"] = player->GetAttack();
        j["exp"] = player->GetExperience();
        j["gold"] = player->GetGold();

        std::ofstream ofs(slotPath(slot));
        if (!ofs) throw std::runtime_error("SaveManager::SaveGame(): 파일열기 실패.");
        ofs << std::setw(4) << j;
        return true;

    }catch (std::exception &e) {
        std::cerr << "SaveManager::SaveGame(): 게임저장 실패: " << e.what() << '\n';
        return false;
    }

}

// 게임 불러오기
bool SaveManager::LoadGame(Character *player, const std::string& slot) {

    try {
        std::ifstream ifs(slotPath(slot));
        if (!ifs) return false; // 파일 없음
        json j; ifs >> j;

        player->SetName(j.value("name", "???"));
        player->SetMaxHealth(j.value("max_health", 100));
        player->SetHealth(j.value("hp", 100));
        player->SetLevel(j.value("level", 1));
        player->SetAttack(j.value("attack", 1));
        player->SetExperience(j.value("exp", 0));
        player->SetGold(j.value("gold", j.value("gold", 0)));

        std::cout << "서둘러 빛나는 게임을 불러오겠습니다." << slot << std::endl;
        return true;
    }catch (const std::exception &e) {
        std::cerr << "역직렬화 오류 : 불러오기 실패" << e.what() << std::endl;
        return false;
    }
}