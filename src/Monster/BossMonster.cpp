#include "../../include/Monster/BossMonster.h"
#include "../../include/Monster/BossMonster.h"
#include "../../include/Monster/MonsterBase.h"
#include "../../include/Monster/MonsterDefinition.h"
#include <cstdlib>

BossMonster::BossMonster(int Level)

    : MonsterBase(
        MonsterDefinition{
            "보스대머리 — 진영형님",        // name
            120 + Level * 10,              // HP
            50,                            // MP (원하는 값 넣어도 됨)
            12 + Level * 4,                // Attack
            {
                "내 반사광은… 모든 걸 태운다.",
                "태양은 잠들어도… 난 빛난다.",
                "내 정수리는 거울이 아니다. 무기다.",
                "빛이 부족한 자여, 고개를 숙여라.",
                "네 두피엔 흔들림이 있다. 난… 완성된 평면이다."
            },
            {}                             // DropTable (비워도 OK)
        },
        Level)


// 턴 활용
void BossMonster::GetTurn() {
    if (CurrentMP >= 20) {
        std::cout << GetName() << " 탈모-빔!\n";
        CurrentMP -= 20;
    }
    else {
        MonsterBase::GetTurn();
    }
}
