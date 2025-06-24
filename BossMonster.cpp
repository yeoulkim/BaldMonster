#include "BossMonster.h"
#include <cstdlib>

BossMonster::BossMonster(int Level)
{
    Name = "보스대머리 — 진영형님";
    Health = 120 + Level * 10;
    Attack = 12 + Level * 4;
    Lines = {
        "내 반사광은… 모든 걸 태운다.",
        "태양은 잠들어도… 난 빛난다.",
        "내 정수리는 거울이 아니다. 무기다.",
        "빛이 부족한 자여, 고개를 숙여라.",
        "네 두피엔 흔들림이 있다. 난… 완성된 평면이다."
    };
}

std::string BossMonster::GetName() const { return Name; }

std::string BossMonster::GetRandomLine()
{
    if (Lines.empty()) return "...";
    int Index = rand() % Lines.size();
    return Lines[Index];
}

int BossMonster::GetHealth() const { return Health; }
int BossMonster::GetAttack() const { return Attack; }

void BossMonster::TakeDamage(int Damage)
{
    Health -= Damage;
    if (Health < 0) Health = 0;
}
