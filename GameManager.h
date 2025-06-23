#pragma once

#include "UObjectBase.h"
#include "Character.h"
#include "BattleSystem.h"
#include "MonsterBase.h"
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
    void StartRandomBattle(Character* Player);
    void LevelUp();
    // void EndGame(); 
    void VisitShop();
    void DisplayInventory(Character* Player);
    void ShowGameLog(std::string Message);
    void ResetGame();

private:
    Character* Player = nullptr;
    int Gold = 0;
	int MaxHealth = 200;
    int MaxExperience = 100;
    int MaxLevel = 10;
    int InventorySize = 0;
    std::vector<std::string> GameLog;
    bool bIsFirstPlay = true;
};