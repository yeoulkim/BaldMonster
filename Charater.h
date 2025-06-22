#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Item.h"  // 아이템 클래스 헤더파일 포함

using namespace std;

class Character {
public:
    // 생성자
    Character(string n, int h, int a, int l);

    // 상태 출력
    void DisplayStatus();

    // 아이템 관련
    void AddItem(Item item);
    void UseItem(string itemName);
    void DisplayInventory();

    // 경험치/레벨업
    void GainExperience(int amount);

    // Getter 함수들
    string GetName() const;
    int GetHealth() const;
    int GetMaxHealth() const;
    int GetAttack() const;
    int GetLevel() const;
    int GetGold() const;
    vector<Item> GetInventory() const;

private:
    // 기본 정보
    string name;
    int health;
    int maxHealth;
    int attack;
    int level;

    // 성장 관련
    int experience;
    int maxExperience;
    int maxLevel;

    // 경제 관련
    int gold;

    // 인벤토리
    int inventorySize;
    vector<Item> inventory;
};

#endif // CHARACTER_H