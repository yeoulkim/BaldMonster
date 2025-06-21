#include "GameManager.h"

int main()
{
    GameManager* Manager = new GameManager();
    Manager->Run();  // ✅ 언리얼처럼 BeginPlay → Tick 반복 실행
    delete Manager;
    return 0;
}
