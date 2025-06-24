#include "Character.h"
#include <iostream>
#include <iomanip>
#include "AttackItem.h"

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

    std::cout << "\n[획득] \"" << NewItem->GetName() << "\" 을(를) 손에 넣었다.\n";
    std::cout << "[설명] " << NewItem->GetAcquireMessage() << "\n";
}

void Character::UseItem(const std::string& ItemName)
{
    for (auto It = Inventory.begin(); It != Inventory.end(); ++It)
    {
        if ((*It)->GetName() == ItemName)
        {
            std::cout << "\n[사용] \"" << ItemName << "\" 을(를) 사용합니다...\n";

            // AttackItem인지 검사해서 AttackItem을 사용
            AttackItem* Attack = dynamic_cast<AttackItem*>(*It);
            if (Attack)
            {
                // 먼저 아이템의 효과를 출력하고, 그 후 AttackItem::Use에서 타겟 공격 메시지가 출력됨
                std::cout << "[효과] " << (*It)->GetAcquireMessage() << "\n";
                Attack->Use(this);  // AttackItem의 Use 함수 호출 (타겟 이름과 피해량 출력됨)
            }
            else
            {
                // 일반 아이템이면 기존대로 Use 호출
                (*It)->Use(this);
                std::cout << "[효과] " << (*It)->GetAcquireMessage() << "\n";
            }

            delete* It;
            Inventory.erase(It);
            std::cout << "[사용 완료] " << ItemName << " 이(가) 소멸 됐습니다.\n";
            return;
        }
    }

    std::cout << "\n[실패] \"" << ItemName << "\" 은(는) 손에 들고 있지 않습니다.\n";
}


// 틀 맞추기
void Character::CheckInventory()
{
    std::cout << "\n┌───────────  탈모 생존 키트  ───────────┐\n";

    if (Inventory.empty())
    {
        std::cout << "│  아직 두피를 지킬 아이템이 없습니다.   │\n";
    }
    else
    {
        for (auto* Item : Inventory)
        {
            std::cout << "│  - " << std::left << std::setw(15) << Item->GetName() << "                     │" << "\n";
        }
    }

    std::cout << "└────────────────────────────────────────┘\n";
}

void Character::TakeDamage(int Damage)
{
    Health -= Damage;
    if (Health < 0)
    {
        Health = 0;
    }

    std::cout << Name << "이(가) " << Damage << "의 피해를 입었다. 모근이 흔들린다...\n";
}


void Character::SetAttackBoost(float Multiplier)
{
    AttackMultiplier = Multiplier;  // 단순히 공격력 배율만 설정
    std::cout << Name << "의 머리카락에 광택이 살아났다! (×" << Multiplier << " 공격력)\n";
}


int Character::GetAttack() const
{
    if (bAttackBoosted && BoostedTurnCount > 0)
    {
        return static_cast<int>(Attack * AttackMultiplier);
    }
    return Attack;
}

void Character::Heal(int Amount)
{
    Health += Amount;
    if (Health > MaxHealth)
    {
        Health = MaxHealth;
    }

    std::cout << Name << "이(가) 두피에 활력을 되찾았다! +" << Amount << " 체력 (현재 체력: " << Health << ")\n";
}

// 매 턴마다 호출되어 공격력 강화 상태를 업데이트
void Character::UpdateTurn()
{
    if (BoostedTurnCount > 0)
    {
        BoostedTurnCount--;

        if (BoostedTurnCount == 0)
        {
            bAttackBoosted = false;
            AttackMultiplier = 1.0f;
            std::cout << Name << "의 광택 효과가 사라졌다. 머릿결이 상했다...\n";
        }
    }
}


void Character::GainExperience(int Amount)
{
    Experience += Amount;
    std::cout << "[경험치] +" << Amount << " 경험치를 흡수했다!\n";

    while (Experience >= MaxExperience && Level < MaxLevel)
    {
        Experience -= MaxExperience;
        Level++;
        MaxHealth += 20;
        Health = MaxHealth;
        Attack += 5;

        std::cout << "\n[↑] 레벨업! 당신의 두피가 한층 더 단단해졌다.\n";
        std::cout << "▶ 현재 레벨: " << Level << " | 체력: " << MaxHealth << " | 공격력: " << Attack << "\n";
    }
}

// Getter 함수
std::string Character::GetName() const { return Name; }
int Character::GetHealth() const { return Health; }
int Character::GetMaxHealth() const { return MaxHealth; }
int Character::GetLevel() const { return Level; }
int Character::GetGold() const { return Gold; }
int Character::GetExperience() const { return Experience; }


// Setter 함수
void Character::SetExperience(int NewExp) { Experience = NewExp; }
void Character::SetGold(int NewGold) { Gold = NewGold; }
void Character::SetHealth(int NewHealth) { Health = NewHealth; }
void Character::SetLevel(int NewLevel) { Level = NewLevel; }

std::vector<Item*> Character::GetInventory() const {
    return Inventory;
}