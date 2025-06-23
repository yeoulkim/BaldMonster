#include "GameManager.h"
#include "Character.h"
#include "YellowMonster.h"
#include "BossMonster.h"

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <ctime>

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
    delete Player;
}
void Intro()
{
    std::cout << "\n";
    Sleep(1000);

    std::cout << "> \"...난 아직 탈모약을 믿는다.\"\n\n";
    Sleep(1500);

    std::cout << "> \"머리카락을 되찾기 위해, 난 그들을 벗겨버릴 것이다.\"\n\n";
    Sleep(1500);

    std::cout << "> \"난 마지막 모발 보유자다…\n";
    std::cout << "내 머리를 건들면… 가만 안 둬.\"\n\n";
    Sleep(2000);

    std::cout << "지금,\n\n";
    Sleep(1000);

    std::cout << "머머리 군단에 맞서는\n\n";
    Sleep(1000);

    std::cout << "최후의 모발 전쟁이 시작된다.\n\n";
    Sleep(2000);

    std::cout << "========================================\n";
    std::cout << "머리카락을 걸고 싸우시겠습니까? [Y/N]: ";

    char Input;
    std::cin >> Input;
    std::cin.ignore();

    if (Input == 'Y' || Input == 'y')
    {
        std::cout << "\n모근을 다잡고, 전장으로 나아갑니다...\n";
        Sleep(1500);
    }
    else
    {
        std::cout << "\n당신은... 민둥산의 길을 택했습니다.\n";
        Sleep(1500);
        std::cout << "이제, 당신도 머머리입니다.\n";
        Sleep(1500);
        exit(0);
    }
}

void GameManager::BeginPlay()
{
    Intro();

    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << "\n===== [ 대머리 연합군 등록소 ] =====\n";
    std::string Name;
    std::cout << "머리카락 보유자여, 이름을 남기시오: ";
    std::getline(std::cin, Name);

    CreateCharacter(Name);
    AddLog("등록 완료. 당신은 이제 머리카락을 지킬 준비가 되었다.");
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
    std::cout << "\x1B[36m";
    std::cout << "\n[O] 당신의 모근은 아직 버티고 있다.\n";
    std::cout << "다음 작전을 선택한다.\n";
    std::cout << "----------------------------------------\n";
    std::cout << "[1] 대머리 군단과 교전한다.\n";
    std::cout << "[2] 탈모약 상점에 방문한다.\n";
    std::cout << "[3] 남아 있는 모발 상태를 진단한다.\n";
    std::cout << "[4] 전장을 떠나 대머리의 길을 걷는다.\n";
    std::cout << "----------------------------------------\n";
    std::cout << "입력 >> ";
    std::cout << "\x1B[0m";

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
        std::cout << "\n당신은 머리를 숙였습니다... 전장을 떠납니다.\n";
        Sleep(1500);
        return;
    default:
        std::cout << "\n그런 선택지는 없다. 머리 식히고 다시 선택하라.\n";
        break;
    }

    system("pause");
}

void GameManager::Run()
{
	BeginPlay();    // BeginPlay() 호출로 게임 시작

	while (bIsTickEnabled)  // bIsTickEnabled가 true인 동안 게임 루프 실행
    {
        Tick(0.016f);
    }
}

void GameManager::CreateCharacter(std::string Name)
{
    Player = new Character(Name);
    Player->SetHealth(200);
    Player->SetLevel(1);
    Player->SetExperience(0);
    Player->SetGold(0);
}

void GameManager::DisplayStatus(int Level)
{
    std::ostringstream oss;

    std::string name = Player->GetName();
    std::string level = "Lv." + std::to_string(Player->GetLevel());
    std::string hp = std::to_string(Player->GetHealth()) + " / " + std::to_string(MaxHealth);
    std::string exp = std::to_string(Player->GetExperience()) + " / " + std::to_string(MaxExperience);
    std::string gold = std::to_string(Player->GetGold()) + " G";

    std::cout << "\n┌───────────────────── 두피 상태 리포트 ─────────────────────┐\n";
    std::cout << "│ 코드네임        : " << std::left << std::setw(40) << name << " │\n";
    std::cout << "│ 성장 등급       : " << std::left << std::setw(40) << level << " │\n";
    std::cout << "│ 두피 내구도     : " << std::left << std::setw(40) << hp << " │\n";
    std::cout << "│ 모근 경험치     : " << std::left << std::setw(40) << exp << " │\n";
    std::cout << "│ 확보 자금       : " << std::left << std::setw(40) << gold << " │\n";
    std::cout << "└────────────────────────────────────────────────────────────┘\n";
}


void GameManager::AddLog(std::string Message)
{
    GameLog.push_back(Message);
    std::cout << "[로그] " << Message << std::endl;
}

void GameManager::ShowGameLog(std::string Message)
{
    std::cout << "[로그] " << Message << std::endl;
}

void GameManager::Battle(MonsterBase* Enemy, Character* Player)
{
    std::cout << "\n[!] 작전 개시. 두피 전장에 진입한다.\n";
    std::cout << ">> 목표 식별: " << Enemy->GetName() << "\n";
    std::cout << Enemy->GetName() << ": \"" << Enemy->GetRandomLine() << "\"\n";

    system("pause >nul");

    while (Player->GetHealth() > 0 && Enemy->GetHealth() > 0)
    {
        int DamageToEnemy = Player->GetAttack();
        Enemy->TakeDamage(DamageToEnemy);
        std::cout << "[공격] " << Enemy->GetName() << "에게 " << DamageToEnemy << " 피해를 입혔다. (남은 체력: " << Enemy->GetHealth() << ")\n";

        system("pause >nul");

        if (Enemy->GetHealth() <= 0)
        {
            std::cout << "[V] " << Enemy->GetName() << " 제거 완료.\n";

            int ExpReward = 20;
            int GoldReward = 10 + (std::rand() % 41);

            Player->SetExperience(Player->GetExperience() + ExpReward);
            Player->SetGold(Player->GetGold() + GoldReward);

            std::cout << "[보상] 모근 경험치 +" << ExpReward << " | 자금 +" << GoldReward << " G\n";

            AddLog("작전 성공. 대머리 대상 제압 완료.");

            if (Player->GetExperience() >= MaxExperience)
            {
                Player->SetExperience(0);
                Player->SetLevel(Player->GetLevel() + 1);
                Player->SetHealth(200);
                std::cout << "[↑] 레벨업! 현재 레벨: " << Player->GetLevel() << "\n";
                AddLog("당신의 두피가 한층 단단해졌다.");
            }

            return;
        }

        int BeforeHP = Player->GetHealth();
        Player->TakeDamage(Enemy->GetAttack());
        int AfterHP = Player->GetHealth();

        if (BeforeHP == AfterHP)
            std::cout << "[회피] 민첩한 빗질로 공격을 피했다.\n";
        else
            std::cout << "[피해] " << (BeforeHP - AfterHP) << " 데미지 입음. (잔여 체력: " << AfterHP << ")\n";

        system("pause >nul");
    }

    if (Player->GetHealth() <= 0)
    {
        std::cout << "[X] 당신은 쓰러졌다. 머리카락을 지키지 못했다...\n";
        AddLog("작전 실패. 두피가 무너졌다.");
    }
}

void GameManager::StartRandomBattle(Character* Player)
{
    MonsterBase* Enemy = nullptr;
    int Level = Player->GetLevel();

    std::cout << "\n[!] 적 생체 반응 감지됨. 전투 모드로 전환한다.\n";

    if (Level >= 10)
    {
        std::cout << "[BOSS] 반사광이 급격히 강해진다... 진형형님이 나타났다.\n";
        Enemy = new BossMonster(Level);
    }
    else
    {
        Enemy = new YellowMonster(Level); // 테스트용 1체
        std::cout << "[적 등장] 스캔 완료: 야생의 노란 대머리와 조우했다.\n";
    }

    Battle(Enemy, Player);
    delete Enemy;
}


void GameManager::EndGame()
{
    std::cout << "\n당신은 도약 대신 후퇴를 택했다. 두피는 침묵했다.\n"; 
    ShowGameLog("탈주 감지. 기록: '머리를 지키기엔 용기가 부족했다.'");
}


void GameManager::VisitShop()
{
    std::cout << "\n=== 상점 ===\n";
    std::cout << "1. 체력 회복 (20골드)\n";
    std::cout << "2. 아무것도 안 함\n";
    std::cout << "입력 >> ";

    int Input;
    std::cin >> Input;
    std::cin.ignore();

    if (Input == 1 && Player->GetGold() >= 20)
    {
        Player->SetHealth(100);
        Player->SetGold(Player->GetGold() - 20);
        AddLog("상점에서 체력을 회복했습니다.");
    }
    else if (Input == 1)
    {
        AddLog("골드가 부족합니다.");
    }
    else
    {
        AddLog("상점을 그냥 나왔습니다.");
    }
}
