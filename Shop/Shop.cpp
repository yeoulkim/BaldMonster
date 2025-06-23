#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

Shop::Shop() {
    availableItems.push_back(new HealthPotion());
    availableItems.push_back(new AttackBoost());
}

Shop::~Shop() {
    for (Item* item : availableItems) {
        delete item;
    }
    availableItems.clear();
}

void Shop::displayItems() {
    for (size_t i = 0; i < availableItems.size(); ++i) {
        std::cout << i + 1 << ". " << availableItems[i]->getName();

        if (availableItems[i]->getName() == "Health Potion")
            std::cout << " (체력 +50): 10 골드";
        else if (availableItems[i]->getName() == "Attack Boost")
            std::cout << " (공격력 +10): 15 골드";

        std::cout << std::endl;
    }
}

void Shop::buyItem(int index, Character* player) {
    if (index < 0 || index >= static_cast<int>(availableItems.size())) return;

    Item* item = availableItems[index];
    int price = (item->getName() == "Health Potion") ? 10 : 15;

    if (player->gold >= price) {
        player->gold -= price;
        player->inventory.push_back(item->clone());
        std::cout << item->getName() << "을(를) 구매했습니다!" << std::endl;
    }
    else {
        std::cout << "골드가 부족합니다." << std::endl;
    }
}

void Shop::sellItem(int index, Character* player) {
    if (index < 0 || index >= static_cast<int>(player->inventory.size())) return;

    Item* item = player->inventory[index];
    int price = (item->getName() == "Health Potion") ? 10 : 15;
    int sellPrice = static_cast<int>(price * 0.6);

    player->gold += sellPrice;
    player->inventory.erase(player->inventory.begin() + index);
    std::cout << item->getName() << "을(를) " << sellPrice << " 골드에 판매했습니다." << std::endl;
    delete item;
}

void Shop::visitShop(Character* player) {
    while (true) {
        std::cout << "\n상점에 오신 것을 환영합니다!\n보유 골드: " << player->gold << std::endl;
        displayItems();
        std::cout << "3. 아이템 판매\n0. 상점 나가기\n선택: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) break;
        else if (choice >= 1 && choice <= 2) {
            buyItem(choice - 1, player);
        }
        else if (choice == 3) {
            if (player->inventory.empty()) {
                std::cout << "판매할 아이템이 없습니다." << std::endl;
                continue;
            }

            for (size_t i = 0; i < player->inventory.size(); ++i) {
                std::string name = player->inventory[i]->getName();
                int price = (name == "Health Potion") ? 6 : 9;
                std::cout << i + 1 << ". " << name << " - 판매가: " << price << std::endl;
            }

            std::cout << "판매할 아이템 번호 (0: 취소): ";
            int sellIdx;
            std::cin >> sellIdx;

            if (sellIdx > 0 && sellIdx <= static_cast<int>(player->inventory.size())) {
                sellItem(sellIdx - 1, player);
            }
        }
    }
}
