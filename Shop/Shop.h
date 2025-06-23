#pragma once  // 헤더 파일 중복 포함 방지

#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

class Shop {
private:
    std::vector<Item*> availableItems; // 상점에 등록된 아이템

public:
    Shop(); // 생성자
    ~Shop(); // 소멸자

    void displayItems();                        // 아이템 목록 출력
    void buyItem(int index, Character* player); // 아이템 구매
    void sellItem(int index, Character* player);// 아이템 판매
    void visitShop(Character* player);          // 상점 메뉴
};
