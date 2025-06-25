#include "GameManager/GameManager.h"

GameManager* GManager = nullptr; // ✅ 전역 객체 정의

int main()
{
    GManager = new GameManager();   // ✅ 전역 포인터로 생성
    GManager->Run();                // ✅ GameManager 안에서 BeginPlay → Tick
    delete GManager;                // ✅ 메모리 정리
    return 0;
}
//기존
