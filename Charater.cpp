#include "Character.h"
#include <iostream>

using namespace std;

Character::Character(string n, int h, int a, int l)
    : name(n), health(h), maxHealth(h), attack(a), level(l),
    experience(0), maxExperience(100), maxLevel(10), gold(0), inventorySize(10) {
}

void Character::DisplayStatus() {
    cout << "===== 캐릭터 상태 =====" << endl;
    cout << "이름: " << name << endl;
    cout << "레벨: " << level << endl;
    cout << "체력: " << health << " / " << maxHealth << endl;
    cout << "공격력: " << attack << endl;
    cout << "경험치: " << experience << " / " << maxExperience << endl;
    cout << "골드: " << gold << endl;
    cout << "======================" << endl;
}

void Character::AddItem(Item item) {
    if (inventory.size() >= inventorySize) {
        cout << "인벤토리가 가득 찼습니다!" << endl;
        return;
    }
    inventory.push_back(item);
    cout << item.name << "을(를) 획득했습니다!" << endl;
}

void Character::UseItem(string itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == itemName) {
            health += it->effect;
            if (health > maxHealth) health = maxHealth;
            cout << itemName << " 사용! 체력이 회복되었습니다." << endl;
            inventory.erase(it);
            return;
        }
    }
    cout << itemName << " 아이템이 없습니다!" << endl;
}

void Character::DisplayInventory() {
    cout << "===== 인벤토리 =====" << endl;
    if (inventory.empty()) {
        cout << "비어 있습니다." << endl;
    }
    else {
        for (const auto& item : inventory) {
            cout << item.name << " (효과: " << item.effect << ")" << endl;
        }
    }
    cout << "===================" << endl;
}

void Character::GainExperience(int amount) {
    experience += amount;
    cout << amount << " 경험치를 획득했습니다!" << endl;

    while (experience >= maxExperience && level < maxLevel) {
        experience -= maxExperience;
        level++;
        maxHealth += 20;
        health = maxHealth;
        attack += 5;
        cout << "레벨 업! 현재 레벨: " << level << endl;
    }
}

// Getter 함수 구현
string Character::GetName() const { return name; }
int Character::GetHealth() const { return health; }
int Character::GetMaxHealth() const { return maxHealth; }
int Character::GetAttack() const { return attack; }
int Character::GetLevel() const { return level; }
int Character::GetGold() const { return gold; }
vector<Item> Character::GetInventory() const { return inventory; }