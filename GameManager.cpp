// 📌 부모 클래스: UObjectBase (언리얼 스타일 흉내)
#pragma once
#include "GameManager.h"
#include <iostream>
#include <thread>
#include <chrono>

class UObjectBase
{
public:
    UObjectBase();
    virtual ~UObjectBase();

    void Run();  // BeginPlay -> Tick 반복 실행

protected:
    bool bIsTickEnabled;
    float DeltaTime;

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
};

// 📌 부모 클래스 구현
#include "UObjectBase.h"

UObjectBase::UObjectBase()
{
    bIsTickEnabled = true;
    DeltaTime = 0.5f;
}

UObjectBase::~UObjectBase() {}

void UObjectBase::Run()
{
    BeginPlay();

    while (bIsTickEnabled)
    {
        Tick(DeltaTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(DeltaTime * 1000)));
    }
}

void UObjectBase::BeginPlay()
{
    std::cout << "[UObjectBase] BeginPlay()\n";
}

void UObjectBase::Tick(float DeltaTime)
{
    std::cout << "[UObjectBase] Tick: " << DeltaTime << "초 경과\n";
}

// 📌 GameManager 클래스 상속 버전
#include "GameManager.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

GameManager::GameManager()
{
    std::cout << "게임 매니저 초기화...\n";
}

GameManager::~GameManager()
{
    std::cout << "게임 매니저 종료...\n";
    delete Player;
}

void GameManager::BeginPlay()
{
    std::cout << "===== 대머리 나라에 오신 걸 환영합니다! =====\n";
    std::string Name;
    std::cout << "캐릭터 이름을 입력하세요: ";
    std::getline(std::cin, Name);

    CreateCharacter(Name);
    AddLog("캐릭터 생성 완료.");
    DisplayStatus(1);
}

void GameManager::Tick(float DeltaTime)
{
    if (Player == nullptr || Player->GetHealth() <= 0 || Player->GetLevel() >= MaxLevel)
    {
        bIsTickEnabled = false;
        EndGame();
        return;
    }

    std::cout << "\n다음 행동을 선택하세요:\n";
    std::cout << "1. 전투 시작\n";
    std::cout << "2. 상점 방문\n";
    std::cout << "3. 상태 보기\n";
    std::cout << "4. 게임 종료\n";
    std::cout << "입력 >> ";

    int Choice;
    std::cin >> Choice;
    std::cin.ignore();

    switch (Choice)
    {
    case 1:
        StartRandomBattle(Player);
        break;
    case 2:
        VisitShop();
        break;
    case 3:
        DisplayStatus(1);
        break;
    case 4:
        bIsTickEnabled = false;
        break;
    default:
        std::cout << "잘못된 선택입니다. 다시 입력하세요.\n";
        break;
    }

    system("pause");
}
