#pragma once  // 헤더 파일 중복 포함 방지

#include "Character.h"
#include "Item.h"
#include <vector>
#include <string>

class Shop {
private:
    std::vector<Item> availableItems; // 상점에 등록된 아이템

public:
    Shop(); //생성

    void displayItems();                        // 아이템 목록 출력
    void buyItem(int index, Character* player); // 아이템 구매
    void sellItem(int index, Character* player);// 아이템 판매
    void visitShop(Character* player);          // 상점 메뉴 (얘도 게임매니저 or sHop 둘중하나 선택_)
};

// 리뉴얼: 외부 시스템(GameManager)에서 연동 가능하도록 이름 기반 아이템 구매
bool buyBasicItem(const std::string& itemName, Character* player);
};