#pragma once
#include <vector>
#include <string>
#include "GameManager.h"

class Character;
class Monster;
class BossMonster;
class Item;
class Shop;

class GameManager 
{
public:
    GameManager();
    ~GameManager();

    void startGame();
    void endGame();

private:
    class Character* Player = nullptr;
    class Shop* GameShop = nullptr;
    std::vector<std::string> GameLog;

    // 초기화
    int Level = 1;
    int MaxLevel = 10;
    int Experience = 0;
    int MaxExperience = 100;
    int Health = 200;
    int MaxHealth = 200;
    int Attack = 30;
    int Gold = 0;
    int InventorySize = 10;

    void GameLoop();
    void CreateCharacter(std::string Name);
    void DisplayStatus();   // Player의 상태 직접 사용
    void LevelUp(int Level);
    void Battle(class Monster* Enemy, class Character* Player);
    class Monster* GenerateMonster(int Level);
    class BossMonster* GenerateBossMonster(int Level);
    void VisitShop();  
    void DisplayInventory(class Character* Player);  
    void ShowGameLog(std::string Message); 
    void AddLog(std::string Message);
};
