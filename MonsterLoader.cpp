//
// Created by suaio on 2025-06-24.
//
#include "../include/MonsterLoader.h"
#include "../include/nlormann/json.hpp"

#include <fstream>
#include <sstream>

/*
 * nlohmann JSON 파싱 외부라이브러리
 * JSON 파일 파싱해서 몬스터 생성
 * readJsonFile
 * LoadMonster
 */

using json = nlohmann::json;

static json readJsonFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) throw std::runtime_error("Cannot open file: " + path);
    json j;
    ifs >> j;
    return j;
}

MonsterDefinition LoadMonster(const std::string& path) {
    json j = readJsonFile(path);

    MonsterDefinition def;
    def.name        = j.value("name", "");
    def.HP  = j.value("baseHealth", 0);
    def.MP      = j.value("baseMP", 0);
    def.Attack  = j.value("baseAttack", 0);
    def.lines       = j.value("lines", std::vector<std::string>{});

    // dropTable 처리
    if (j.contains("dropTable")) {
        for (const auto& entry : j["dropTable"]) {
            std::string item = entry.value("itemName", "");
            double rate = entry.value("dropRate", 0.0);
            if (!item.empty()) {
                def.DropTable.push_back({ item, rate });
            }
        }
    }

    return def;
}
