//
// Created by suaio on 2025-06-24.
//

#include "../../include/Monster/MonsterBase.h"
#include "../../include/Item/Item.h"
#include "../../include/Item/ItemFactory.h"
#include <random>
#include <iostream>

// Random Number Generator 사용
static std::mt19937 rng{std::random_device{}()};

// 생성자
MonsterBase::MonsterBase(MonsterDefinition def, int level)
    : def(std::move(def)), Level(level) {
    CurrentHP = this->def.HP + level * 5;
    CurrentMP = this->def.MP + level * 3;
}

std::string MonsterBase::GetName() const {return def.name;};
int MonsterBase::GetHP() const {return CurrentHP;};
int MonsterBase::GetMP() const {return CurrentMP;};
int MonsterBase::GetAttack() const {return def.Attack + Level * 2;}

void MonsterBase::GetDamaged(int dmg) {
    CurrentHP -= dmg;
    if (CurrentHP < 0) CurrentHP = 0;
}

std::string MonsterBase::GetRandomLines() const {
    if (def.lines.empty()) return "...";
    std::uniform_int_distribution<int> dist(0, static_cast<int>(def.lines.size()) - 1);
    return def.lines[dist(rng)];
}

void MonsterBase::GetTurn() {
    if (CurrentMP >= 10) {
        std::cout << GetName() << " (스킬명)!\n";
        CurrentMP -= 10;
    } else {
        std::cout << GetName() << " 기본공격!\n";
    }
}

std::unique_ptr<Item> MonsterBase::DropItem() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    double roll = dist(rng);
    double cumulative = 0.0;

    for (const auto& entry : def.DropTable) {
        cumulative += entry.DropRate;
        if (roll <= cumulative) {
            return CreateItem(entry.ItemName);
        }
    }
    return nullptr;
}