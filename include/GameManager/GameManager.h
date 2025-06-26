#pragma once

#include "UObjectBase.h"
#include "../../include/Character/Character.h"
#include "BattleSystem.h"
#include "../../include/Monster/MonsterBase.h"
#include "../../include/Item/Item.h"
// #include "YellowMonster.h"
// #include "BossMonster.h"
// #include "Shop.h"
#include <string>
#include <vector>

class GameManager : public UObjectBase
{
public:
    GameManager();
    virtual ~GameManager();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    void Run();

    void CreateCharacter(std::string Name);
    void DisplayStatus(int Level);
    void AddLog(std::string Message);
    void LevelUp();

    void VisitShop();
    void DisplayInventory(Character* Player);
    void ShowShopItems(const std::vector<Item*>& ShopItems);

    void ShowGameLog(std::string Message);
    void ResetGame();

    std::vector<Item*> GetHealingShopItems();
    std::vector<Item*> GetAttackShopItems();

    // Random 몬스터 생성
    MonsterBase* SummonRandomMonster(int PlayerLevel, int Difficulty = 1);

    void DungeonMenu(Character* player);
    void StartRandomBattle(Character* Player, int Difficulty = 1);
    void StartBossBattle(Character * player);

private:
    Character* Player = nullptr;
    int Gold = 0;
    //int MaxHealth = 200;
    int MaxExperience = 100;
    int MaxLevel = 10;
    int InventorySize = 0;
    std::vector<std::string> GameLog;
    bool bIsFirstPlay = true;
};