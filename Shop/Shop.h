#pragma once

#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

class Shop {
private:
    std::vector<Item> availableItems;  // 값 형태로 아이템 저장

public:
    Shop();

    void displayItems();                              // 아이템 목록 출력
    void buyItem(int index, Character* player);       // 아이템 구매
    void sellItem(int index, Character* player);      // 아이템 판매

    // 리뉴얼: 외부 시스템(GameManager)에서 연동 가능하도록 이름 기반 아이템 구매
    bool buyBasicItem(const std::string& name, Character* player); 
};