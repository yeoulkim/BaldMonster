#pragma once

#include "Item.h"
#include <string>
#include <vector>

class Character
{
public:
    // 생성자
    Character(std::string Name, int Health, int Attack, int Level);

    // 아이템 관련
    void AddItem(Item* NewItem);
    void UseItem(const std::string& ItemName);
    void DisplayInventory();
    std::vector<Item*> GetInventory() const;

    // 경험치/레벨업
    void GainExperience(int Amount);

    // Getter
    std::string GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetLevel() const;
    int GetGold() const;
    int GetExperience() const;

    // Setter
    void SetExperience(int NewExp);
    void SetGold(int NewGold);
    void SetHealth(int NewHealth);
    void SetLevel(int NewLevel);

    void TakeDamage(int Damage)
    {
        Health -= Damage;
        if (Health < 0) Health = 0;
    }

private:
    std::string Name;
    int Health;
    int MaxHealth;
    int Attack;
    int Level;

    int Experience;
    int MaxExperience;
    int MaxLevel;

    int Gold;
    int InventorySize;

    std::vector<Item*> Inventory;  // ✅ 중복 제거 및 포인터 버전 유지
};
