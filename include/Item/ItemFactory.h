#pragma once
#include <memory>
#include <string>
#include "Bible.h"
#include "Brush.h"

inline std::unique_ptr<Item> CreateItem(const std::string& name) {
    if (name == "탈모의 성서") return std::make_unique<Bible>();
    if (name == "고대의 빗") return std::make_unique<Brush>();
    // if (name == "진영형님의 가냘픈 새치 한 가닥") return std::make_unique<Hair>();
    return nullptr;
}
