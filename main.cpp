#include "GameManager.h"

int main()
{
    GameManager* Manager = new GameManager();   // 동적 생성
    Manager->Run();  // 언리얼처럼 BeginPlay → Tick 반복 실행
    delete Manager; // 메모리 정리
    return 0;
}
