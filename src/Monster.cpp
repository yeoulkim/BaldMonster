#include "Monster.h"
// #include <cstdlib>

// 멤버 초기화 리스트 / 이동 ->
Monster::Monster(std::string n,int h,int a):name(std::move(n)),health(h),attack(a){}

// const 멤버 함수 &참조 반환
const std::string& Monster::getName() const { return name; }
int Monster::getHealth() const { return health; }
int Monster::getAttack() const { return attack; }

// 몸스터 상태 변화 구현
void Monster::takeDamage(int dmg){ health-=dmg; if(health<0) health=0; }

// 몬스터 아이템 드랍
std::unique_ptr<Item> Monster::dropItem(){
    if(std::rand()%2==0) return std::make_unique<HealthPotion>();
    else return std::make_unique<AttackBoost>();
}

// 노랭이 생성
Yellow::Yellow(int lvl):Monster("야생의 노란 대머리",40+lvl*5,5+lvl*2){}

//하양이 생성
White::White(int lvl):Monster("신생아 머리",60+lvl*6,7+lvl*2){}

//초록이 생성
Green::Green(int lvl):Monster("쑥 대머리",80+lvl*8,9+lvl*3){}

// 파랭이 생성
Blue::Blue(int lvl):Monster("착한 대머리",80+lvl*8,9+lvl*3){}

// 빨갱이 생성
Pink::Pink(int lvl):Monster("나쁜 대머리",80+lvl*8,9+lvl*3){}

// 깜댕이 생성
Black::Black(int lvl):Monster("진형형님",120+lvl*10,12+lvl*4){}