#include "Shop/Shop.h"
#include "HealingItem.h"
#include "AttackItem.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <limits>

void Shop::EnterShop(Character* Player)
{
    bool bInShop = true;

    while (bInShop)
    {
        std::cout << "\n[안내] 보급소 도착. 전장 투입 전 준비를 마치십시오.\n";
        Sleep(1000);

        std::cout << "\n┌──────────  탈모약 보급소 ──────────┐\n";
        std::cout << "          보유 골드: " << std::right << std::setw(5) << Player->GetGold() << " G                \n";
        std::cout << "  ================================\n";
        std::cout << "   1. 두피 회복용 탈모약 구매        \n";
        std::cout << "   2. 공격형 탈모 도구 구매          \n";
        std::cout << "   3. 보유 아이템 판매               \n";
        std::cout << "   0. 전장으로 복귀                  \n";
        std::cout << "└──────────────────────────────────┘\n";
        std::cout << "당신의 행동을 선택하시오 >> ";

        int Choice;
        if (!(std::cin >> Choice))
        {
            std::cin.clear(); std::cin.ignore(10000, '\n'); continue;
        }
        std::cin.ignore();

        switch (Choice)
        {
        case 0:
            std::cout << "\n[안내] 보급 종료. 전장으로 복귀합니다.\n";
            bInShop = false;
            break;
        case 1:
            ShowBuyMenu(Player);
            break;
        case 2:
            ShowBuyAttackMenu(Player);
            break;
        case 3:
            ShowSellMenu(Player);
            break;
        default:
            std::cout << "[!] 유효하지 않은 선택입니다. 다시 시도하시오.\n";
            break;
        }
    }
}

void Shop::ShowBuyMenu(Character* Player)
{
    std::vector<Item*> Items = GetHealingItems();
    std::cout << "\n┌─────────────  전장 보급 목록 ─────────────┐\n";
    for (size_t i = 0; i < Items.size(); ++i)
    {
        std::cout << "   " << i + 1 << ". " << std::left << std::setw(15) << Items[i]->GetName()
            << " - 가격: " << std::right << std::setw(5) << Items[i]->GetPrice() << " G       \n";
    }
    std::cout << "   0. 보급소 메인으로 돌아가기              \n";
    std::cout << "└─────────────────────────────────────────┘\n";
    std::cout << "당신의 보급 선택을 입력하시오 >> ";

    int Choice;
    std::cin >> Choice;
    std::cin.ignore();

    if (Choice == 0) return;
    if (Choice >= 1 && Choice <= (int)Items.size())
    {
        Item* SelectedItem = Items[Choice - 1];
        int Price = SelectedItem->GetPrice();

        if (Player->GetGold() >= Price)
        {
            Player->SetGold(Player->GetGold() - Price);
            Player->AddItem(SelectedItem);
            std::cout << "[구매 완료] " << SelectedItem->GetName() << "을(를) 구매했습니다.\n";
        }
        else
        {
            std::cout << "[실패] 자금이 부족합니다.\n";
        }
    }
}
void Shop::ShowBuyAttackMenu(Character* Player)
{
    std::vector<Item*> Items = GetAttackItems();
    std::cout << "\n┌────────────  공격형 탈모 도구 목록 ───────────┐\n";
    for (size_t i = 0; i < Items.size(); ++i)
    {
        std::cout << "  " << i + 1 << ". " << std::left << std::setw(20) << Items[i]->GetName()
            << " - 가격: " << std::right << std::setw(5) << Items[i]->GetPrice() << " G       \n";
    }
    std::cout << "  0. 보급소 메인으로 돌아가기              \n";
    std::cout << "└───────────────────────────────────────────┘\n";
    std::cout << "당신의 보급 선택을 입력하시오 >> ";

    int Choice;
    std::cin >> Choice;
    std::cin.ignore();

    if (Choice == 0) return;
    if (Choice >= 1 && Choice <= (int)Items.size())
    {
        Item* SelectedItem = Items[Choice - 1];
        int Price = SelectedItem->GetPrice();

        if (Player->GetGold() >= Price)
        {
            Player->SetGold(Player->GetGold() - Price);
            Player->AddItem(SelectedItem);
            std::cout << "[구매 완료] " << SelectedItem->GetName() << "을(를) 구매했습니다.\n";
        }
        else
        {
            std::cout << "[실패] 자금이 부족합니다.\n";
        }
    }
}

void Shop::ShowSellMenu(Character* Player)
{
    std::vector<Item*> Inventory = Player->GetInventory();

    if (Inventory.empty())
    {
        std::cout << "\n[알림] 판매할 아이템이 없습니다.\n";
        return;
    }

    std::cout << "\n┌────── 판매 가능한 아이템 목록 ──────┐\n";
    for (size_t i = 0; i < Inventory.size(); ++i)
    {
        int SellPrice = Inventory[i]->GetPrice() * 0.6;
        std::cout << "   " << i + 1 << ". " << std::setw(15) << Inventory[i]->GetName()
                  << " - 판매가: " << SellPrice << " G          \n";
    }
    std::cout << "   0. 돌아가기                            \n";
    std::cout << "└─────────────────────────────────┘\n";
    std::cout << "판매할 아이템 번호를 선택하세요 >> ";

    int Choice;
    std::cin >> Choice;
    std::cin.ignore();

    if (Choice >= 1 && Choice <= (int)Inventory.size())
    {
        Item* item = Inventory[Choice - 1];
        int Price = item->GetPrice() * 0.6;
        Player->SetGold(Player->GetGold() + Price);
        Player->RemoveItemByIndex(Choice - 1);
    }
    else if (Choice == 0)
    {
        std::cout << "[안내] 판매를 취소합니다.\n";
    }
    else
    {
        std::cout << "[실패] 잘못된 선택입니다.\n";
    }
}

std::vector<Item*> Shop::GetHealingItems()
{
    std::vector<Item*> items;
    items.push_back(new HealingItem("싸구려 탈모약", 20, "미미한 효과", 30));
    items.push_back(new HealingItem("보통의 탈모약", 50, "무난한 효과", 60));
    items.push_back(new HealingItem("프리미엄 탈모약", 100, "감동적인 효과", 100));
    return items;
}

std::vector<Item*> Shop::GetAttackItems()
{
    std::vector<Item*> items;
    items.push_back(new AttackItem("Combat Brush", 10, "정수리 치기 좋음", EAttackEffect::DirectDamage, 30));
    items.push_back(new AttackItem("Combat Hair Tonic", 30, "부작용 있음", EAttackEffect::DirectDamage, 60));
    return items;
}