#pragma once  //헤더 파일 중복 포함을 방지하는 지시어
#include "Character.h"
#include "Item.h"
#include <vector>

class Shop { //상점 클래스 정의
private:
    //상점에서 판매 가능한 아이템 목록을 저장하는 벡터 (포인터로 관리)
    std::vector<Item*> availableItems; 
public:
    Shop(); //생성자 : 상점 초기화 시 아이템 목록 설정
    void displayItems(); //아이템 목록
    void buyItem(int index, Character* player); //구매
    void sellItem(int index, Character* player);//판매
    void visitShop(Character* player); // 상점메뉴 루프처리
};

