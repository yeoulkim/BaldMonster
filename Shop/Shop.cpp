#include "Shop.h"
#include "HealthPotion.h" //체력포션 추후 변경
#include "AttackBoost.h" // 공격포션 추후 변경
#include <iostream>
using namespace std;

Shop::Shop() { //객체를 동적으로 생성하여 추가
    availableItems.push_back(new HealthPotion());//체력포션 추후 변경
    availableItems.push_back(new AttackBoost());// 공격포션 추후 변경
}

void Shop::displayItems() { //아이템 출력 함수 
    for (size_t i = 0; i < availableItems.size(); ++i) { //상점 템 반복
        cout << i + 1 << ". " << availableItems[i]->getName(); //템 번호 이름 출력
        if (availableItems[i]->getName() == "Health Potion") cout << " (체력 +50): 10 골드";  //템 상세 설명 추가
        else if (availableItems[i]->getName() == "Attack Boost") cout << " (공격력 +10): 15 골드";
        cout << endl; 
    }
}

void Shop::buyItem(int index, Character* player) { //특정 인덱스 템을 플레이어가 구매
    if (index < 0 || index >= (int)availableItems.size()) return; //잘못된거 방지
    Item* item = availableItems[index]; //아이템 포인터
    int price = (item->getName() == "Health Potion") ? 10 : 15; //이름에 따라 가격 결정
    if (player->gold >= price) { //돈 확인
        player->gold -= price;
        player->inventory.push_back(item->clone());
        cout << item->getName() << "을(를) 구매했습니다!" << endl;
    }
    else {
        cout << "골드가 부족합니다." << endl;
    } //구매 or 실패 출력
}

void Shop::sellItem(int index, Character* player) { //인벤토리에서 템을 골드로 판매
    if (index < 0 || index >= (int)player->inventory.size()) return; //인덱스 검사
    Item* item = player->inventory[index]; // 가격계산 
    int price = (item->getName() == "Health Potion") ? 10 : 15;
    int sellPrice = static_cast<int>(price * 0.6); //60% 환산
    player->gold += sellPrice; //판매처리
    player->inventory.erase(player->inventory.begin() + index);
    cout << item->getName() << "을(를) " << sellPrice << " 골드에 판매했습니다." << endl;
    delete item; //메모리해제
}

void Shop::visitShop(Character* player) { //상점 루프 시작
    while (true) { //골드, 메뉴 입출력
        cout << "\n상점에 오신 것을 환영합니다!\n보유 골드: " << player->gold << endl;
        displayItems();
        cout << "3. 아이템 판매" << endl;
        cout << "0. 상점 나가기" << endl;
        cout << "선택: ";
        int choice;  
        cin >> choice;

        //구매처리
        if (choice == 0) break;
        else if (choice >= 1 && choice <= 2) {
            buyItem(choice - 1, player);
        }

        // 인벤토리 확인
        else if (choice == 3) {
            if (player->inventory.empty()) {
                cout << "판매할 아이템이 없습니다." << endl;
                continue;
            }// 인벤토리 아이템 나열 및 선택
            for (size_t i = 0; i < player->inventory.size(); ++i) {
                cout << i + 1 << ". " << player->inventory[i]->getName() << " - 판매가: " << ((player->inventory[i]->getName() == "Health Potion") ? 6 : 9) << endl;
            }
            cout << "판매할 아이템 번호 (0: 취소): ";
            int sellIdx;
            cin >> sellIdx;

            //판매 처리  or 루프 
            if (sellIdx > 0 && sellIdx <= (int)player->inventory.size()) {
                sellItem(sellIdx - 1, player);
            }
        }
    }
}
