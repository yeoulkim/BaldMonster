#include "GameManager.h"
#include "Character.h"
#include "Monster.h"
#include "BossMonster.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

GameManager::GameManager()
{
    cout << "게임 매니저 초기화...\n";
}

GameManager::~GameManager()
{
    cout << "게임 매니저 종료...\n";
    delete Player;
}

void GameManager::BeginPlay()
{
    srand(static_cast<unsigned int>(time(0))); // ✅ 이거 추가!

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

    cout << "\n다음 행동을 선택하세요:\n";
    cout << "1. 전투 시작\n";
    cout << "2. 상점 방문\n";
    cout << "3. 상태 보기\n";
    cout << "4. 게임 종료\n";
    cout << "입력 >> ";

    int Choice;
    cin >> Choice;
    cin.ignore();

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
        cout << "잘못된 선택입니다. 다시 입력하세요.\n";
        break;
    }

    system("pause");
}

void GameManager::CreateCharacter(string Name)
{
    Player = new Character(Name);
    Player->SetHealth(200);
    Player->SetLevel(1);
    Player->SetExperience(0);
    Player->SetGold(0);
}

void GameManager::DisplayStatus(int Level)
{
    cout << "\n=== 현재 상태 ===\n";
    cout << "이름: " << Player->GetName() << endl;
    cout << "레벨: " << Player->GetLevel() << endl;
    cout << "체력: " << Player->GetHealth() << " / " << MaxHealth << endl;
    cout << "경험치: " << Player->GetExperience() << " / " << MaxExperience << endl;
    cout << "골드: " << Player->GetGold() << endl;
    cout << "==============\n";
}

void GameManager::AddLog(string Message)
{
    GameLog.push_back(Message);
    cout << "[로그] " << Message << endl;
}

void GameManager::ShowGameLog(std::string Message)
{
    std::cout << "[로그] " << Message << std::endl;
}


void GameManager::Battle(Monster* Enemy, Character* Player)
{
    std::cout << "\n=== 전투 시작! ===\n";
    std::cout << ">> " << Enemy->getName() << " 등장!\n";  // ✅ 전투 시작 시 이름 출력

    while (Player->GetHealth() > 0 && Enemy->getHealth() > 0)
    {
        int DamageToEnemy = Player->GetAttack();
        Enemy->takeDamage(DamageToEnemy);
        std::cout << ">> " << Enemy->getName() << "에게 " << DamageToEnemy << " 데미지를 입혔습니다. (남은 체력: " << Enemy->getHealth() << ")\n";

        if (Enemy->getHealth() <= 0)
        {
            std::cout << ">> " << Enemy->getName() << " 처치 완료!\n";
            // ✅ 골드 & 경험치 보상 추가
            int ExpReward = 50;
            int GoldReward = 10 + (rand() % 41);

            int NewExp = Player->GetExperience() + ExpReward;
            int NewGold = Player->GetGold() + GoldReward;

            Player->SetExperience(NewExp);
            Player->SetGold(NewGold);

            std::cout << ">> 경험치 +" << ExpReward << ", 골드 +" << GoldReward << "\n";
            AddLog("전투에서 승리했습니다.");

            // ✅ 레벨업 조건 검사
            if (NewExp >= MaxExperience)
            {
                Player->SetExperience(0);
                Player->SetLevel(Player->GetLevel() + 1);
                Player->SetHealth(200);
                std::cout << ">> 레벨업! 현재 레벨: " << Player->GetLevel() << "\n";
                AddLog("레벨업 했습니다!");
            }

            return;
        }

        int BeforeHP = Player->GetHealth();
        Player->TakeDamage(Enemy->getAttack());
        int AfterHP = Player->GetHealth();

        if (BeforeHP == AfterHP)
            std::cout << ">> 플레이어가 공격을 회피했습니다!\n";
        else
            std::cout << ">> 플레이어가 " << (BeforeHP - AfterHP) << " 데미지를 입었습니다. (남은 체력: " << AfterHP << ")\n";
    }

    if (Player->GetHealth() <= 0)
    {
        std::cout << ">> 당신은 쓰러졌습니다...\n";
        AddLog("전투에서 패배했습니다.");
    }
}


void GameManager::StartRandomBattle(Character* Player)
{
    Monster* Enemy = nullptr;
    int Level = Player->GetLevel();

    if (Level >= 10)
    {
        Enemy = new Black(Level);  // ✅ 깜댕이(보스)
    }
    else
    {
        int Random = rand() % 5;
        switch (Random)
        {
        case 0: Enemy = new Yellow(Level); break;
        case 1: Enemy = new White(Level);  break;
        case 2: Enemy = new Green(Level);  break;
        case 3: Enemy = new Blue(Level);   break;
        case 4: Enemy = new Pink(Level);   break;
        }
    }

    Battle(Enemy, Player);
    delete Enemy;
}



void GameManager::EndGame()
{
    cout << "\n게임이 종료되었습니다!\n";
    ShowGameLog("플레이어가 게임을 종료했습니다.");
}

void GameManager::VisitShop()
{
    cout << "\n=== 상점 ===\n";
    cout << "1. 체력 회복 (20골드)\n";
    cout << "2. 아무것도 안 함\n";
    cout << "입력 >> ";

    int Input;
    cin >> Input;
    cin.ignore();

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
