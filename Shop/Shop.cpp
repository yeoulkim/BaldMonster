#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

Shop::Shop() {
    availableItems.push_back(HealthPotion());  //체력포션 추후 변경
    availableItems.push_back(AttackBoost());     // 공격포션 추후 변경
}


void Shop::displayItems() {   //아이템 출력 함수
    for (size_t i = 0; i < availableItems.size(); ++i) {  //상점 템 반복
        std::cout << i + 1 << ". " << availableItems[i]->getName();  //템 번호 이름 출력

        if (availableItems[i].getName() == "Health Potion")
            std::cout << " (체력 +50): 10 골드";
        else if (availableItems[i].getName() == "Attack Boost")
            std::cout << " (공격력 +10): 15 골드";

        std::cout << std::endl;  //템 상세 설명 추가
    }
}

void Shop::buyItem(int index, Character* player) {   //특정 인덱스 템을 플레이어가 구매
    if (index < 0 || index >= static_cast<int>(availableItems.size())) return;  //잘못된거 방지

    Item item = availableItems[index];
    int price = (item.getName() == "Health Potion") ? 10 : 15;  //이름에 따라 가격 결정

    if (player->gold >= price) {   //돈 확인
        player->gold -= price;
        player->inventory.push_back(item);
        std::cout << item.getName() << "을(를) 구매했습니다!" << std::endl;
    }
    else {
        std::cout << "골드가 부족합니다." << std::endl;   //구매 or 실패 출력
    }
}

void Shop::sellItem(int index, Character* player) {  //인벤토리에서 템을 골드로 판매
    if (index < 0 || index >= static_cast<int>(player->inventory.size())) return;  //인덱스 검사

    Item item = player->inventory[index];   // 가격계산
    int price = (item.getName() == "Health Potion") ? 10 : 15;
    int sellPrice = static_cast<int>(price * 0.6);  //60% 환산

    player->gold += sellPrice;   //판매처리
    player->inventory.erase(player->inventory.begin() + index);
    std::cout << item.getName() << "을(를) " << sellPrice << " 골드에 판매했습니다." << std::endl;
}

//  리뉴얼 추가: 이름으로 아이템 구매 시도
bool Shop::buyBasicItem(const std::string& itemName, Character* player) {
    for (const Item& item : availableItems) {
        if (item.getName() == itemName) {
            int price = (item.getName() == "Health Potion") ? 10 : 15;
            if (player->gold >= price) {
                player->gold -= price;
                player->inventory.push_back(item);
                return true;
            }
            else {
                return false; // 골드 부족
            }
        }
    }
    return false; // 아이템 없음
}