#include "YellowMonster.h"
#include <cstdlib>

YellowMonster::YellowMonster(int Level)
{
    Name = "야생의 노란 대머리";
    Health = 40 + Level * 5;
    Attack = 5 + Level * 2;
    Lines = {
        "난 샴푸 없이도 야성적이야!",
        "해 뜨면 내 머리 반사돼. 눈 멀 준비 해라!",
        "내 정수리는 사막이야… 누구든 미끄러지지."
    };
}

std::string YellowMonster::GetName() const { return Name; }

std::string YellowMonster::GetRandomLine()
{
    if (Lines.empty()) return "...";
    int Index = rand() % Lines.size();
    return Lines[Index];
}

int YellowMonster::GetHealth() const { return Health; }
int YellowMonster::GetAttack() const { return Attack; }

void YellowMonster::TakeDamage(int Damage)
{
    Health -= Damage;
    if (Health < 0) Health = 0;
}
