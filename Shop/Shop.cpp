#include "Shop.h"
#include "HealthPotion.h"
#include "AttackBoost.h"
#include <iostream>

Shop::Shop() {
availableItems.push_back(HealthPotion());
availableItems.push_back(AttackBoost());
}

void Shop::displayItems() {   //아이템 출력 함수
for (size_t i = 0; i < availableItems.size(); ++i) {  //상점 템 반복
const Item& item = availableItems[i];
std::cout << i + 1 << ". " << item.getName()    //템 번호 이름 출력
<< " - 가격: " << item.getPrice() << " 골드" << std::endl;
}
}

void Shop::buyItem(int index, Character* player) {   //특정 인덱스 템을 플레이어가 구매
if (index < 0 || index >= static_cast<int>(availableItems.size())) return;   //잘못된거 방지

Item item = availableItems[index];
int price = item.getPrice();

if (player->gold >= price) {  //돈 확인
player->gold -= price;
player->inventory.push_back(item);
std::cout << item.getName() << "을(를) 구매했습니다!" << std::endl;
}
else {
std::cout << "골드가 부족합니다." << std::endl;   //구매 or 실패 출력
}
}

void Shop::sellItem(int index, Character* player) {  //인벤토리에서 템을 골드로 판매
if (index < 0 || index >= static_cast<int>(player->inventory.size())) return;

Item item = player->inventory[index];   // 가격계산
int price = item.getPrice();
int sellPrice = static_cast<int>(price * 0.6);  // 판매가는 60%

player->gold += sellPrice;
player->inventory.erase(player->inventory.begin() + index);
std::cout << item.getName() << "을(를) " << sellPrice << " 골드에 판매했습니다." << std::endl;
}

//  리뉴얼 추가: 이름으로 아이템 구매 시도
bool Shop::buyBasicItem(const std::string& itemName, Character* player) {
for (const Item& item : availableItems) {
if (item.getName() == itemName) {
int price = item.getPrice();
if (player->gold >= price) {
player->gold -= price;
player->inventory.push_back(item);
return true;
}
else {
return false;  // 골드 부족
}
}
}
return false;  // 아이템 없음
}
