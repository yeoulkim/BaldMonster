//
// Created by suaio on 2025-06-24.
//

#include <iostream>

#include "../include/MonsterBase.h"
#include "../include/MonsterLoader.h"
#include "../include/BossMonster.h"
// Test
int main(){

    auto yellowDef = LoadMonster("../assets/data/yellow.monster.json");
    MonsterBase yellow(yellowDef, 3);

    std::cout << "Spawned: " << yellow.GetName() << "\n";
    yellow.GetTurn();
    yellow.GetDamaged(15);
    std::cout << "HP after damage: " << yellow.GetHP() << "\n";

    auto bossDef = LoadMonster("../assets/data/boss.monster.json");
    BossMonster boss(bossDef, 10);
    boss.GetTurn();

    if(auto loot = boss.DropItem()){
        // std::cout << "보스 드랍: " << loot -> GetName() << "\n";
        // std::cout << "Boss dropped: " << loot->GetName() << "\n";
    } else {
        std::cout << "드랍 없음\n";
    }

    return 0;
}