#include "Character.h"
#include <iostream>

Character::Character(std::string Name, int Health, int Attack, int Level)
    : Name(Name),
    Health(Health),
    MaxHealth(Health),
    Attack(Attack),
    Level(Level),
    Experience(0),
    MaxExperience(100),
    MaxLevel(10),
    Gold(0),
    InventorySize(10)
{
}

void Character::AddItem(Item* NewItem)
{
    Inventory.push_back(NewItem);
    std::cout << NewItem->GetName() << "��(��) ȹ���߽��ϴ�!" << std::endl;
}

void Character::UseItem(const std::string& ItemName)
{
    for (auto It = Inventory.begin(); It != Inventory.end(); ++It)
    {
        if ((*It)->GetName() == ItemName)
        {
            (*It)->Use(this);       // Character* ����
            delete* It;             // �޸� ����
            Inventory.erase(It);
            return;
        }
    }
    std::cout << ItemName << " �������� �����ϴ�!" << std::endl;
}

void Character::DisplayInventory()
{
    std::cout << "===== �κ��丮 =====" << std::endl;
    for (auto* Item : Inventory)
    {
        std::cout << "- " << Item->GetName() << std::endl;
    }
    std::cout << "====================" << std::endl;
}

std::vector<Item*> Character::GetInventory() const
{
    return Inventory;
}

void Character::GainExperience(int Amount)
{
    Experience += Amount;
    std::cout << Amount << " ����ġ�� ȹ���߽��ϴ�!" << std::endl;
    while (Experience >= MaxExperience && Level < MaxLevel)
    {
        Experience -= MaxExperience;
        Level++;
        MaxHealth += 20;
        Health = MaxHealth;
        Attack += 5;
        std::cout << "���� ��! ���� ����: " << Level << std::endl;
    }
}

// Getter �Լ�
std::string Character::GetName() const { return Name; }
int Character::GetHealth() const { return Health; }
int Character::GetMaxHealth() const { return MaxHealth; }
int Character::GetAttack() const { return Attack; }
int Character::GetLevel() const { return Level; }
int Character::GetGold() const { return Gold; }
int Character::GetExperience() const { return Experience; }


// Setter �Լ�
void Character::SetExperience(int NewExp) { Experience = NewExp; }
void Character::SetGold(int NewGold) { Gold = NewGold; }
void Character::SetHealth(int NewHealth) { Health = NewHealth; }
void Character::SetLevel(int NewLevel) { Level = NewLevel; }
