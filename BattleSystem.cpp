#include "BattleSystem.h"
#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

extern GameManager* GManager;   // GameManager에 접근하기 위해 전역 포인터 사용 -> 배틀시스템 안에서도 ResetGame() 호출 가능

void BattleSystem::StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience)
{
    std::cout << "\n[!] 작전 개시. 두피 전장에 진입한다.\n";
    std::cout << ">> 목표 식별: " << Enemy->GetName() << "\n";
    std::cout << Enemy->GetName() << ": \"" << Enemy->GetRandomLine() << "\"\n";
    system("pause >nul");
    while (Player->GetHealth() > 0 && Enemy->GetHealth() > 0)
    {
        int DamageToEnemy = Player->GetAttack();
        Enemy->TakeDamage(DamageToEnemy);
        std::cout << "[공격] " << Enemy->GetName() << "에게 " << DamageToEnemy
            << " 피해를 입혔다. (남은 체력: " << Enemy->GetHealth() << ")\n";
        system("pause >nul");
        if (Enemy->GetHealth() <= 0)
        {
            std::cout << "[V] " << Enemy->GetName() << " 제거 완료.\n";

            int ExpReward = 20;
            int GoldReward = 10 + (rand() % 41);

            Player->GainExperience(ExpReward);  // ✅ 레벨업 처리 포함

            Player->SetGold(Player->GetGold() + GoldReward);
            std::cout << "[보상] 모근 경험치 +" << ExpReward << " | 자금 +" << GoldReward << " G\n";

            system("pause >nul");
            return;
        
            /*if (NewExp >= MaxExperience)
            {
                Player->SetExperience(0);
                Player->SetLevel(Player->GetLevel() + 1);
                Player->SetHealth(200);
                std::cout << "[↑] 레벨업! 현재 레벨: " << Player->GetLevel() << "\n";
                std::cout << "[=] 당신의 두피가 한층 더 단단해졌다.\n";
                system("pause >nul");
            }*/
            return;
        }
        int BeforeHP = Player->GetHealth();
        Player->TakeDamage(Enemy->GetAttack());
        int AfterHP = Player->GetHealth();
        if (BeforeHP == AfterHP)
            std::cout << "[회피] 민첩한 빗질로 공격을 피했다.\n";
        else
            std::cout << "[피해] " << (BeforeHP - AfterHP)
            << " 데미지 입음. (잔여 체력: " << AfterHP << ")\n";
        system("pause >nul");
    }

    // 게임 오버 처리, 재시작
    if (Player->GetHealth() <= 0)
    {
        std::cout << "[GAME OVER] 당신은 쓰러졌다. 머리카락을 지키지 못했다...\n";
        Sleep(1000);

        std::vector<std::string> GameOverLines = {
            "머머리 군단의 반짝임 앞에… 결국 눈을 감았다.",
            "당신의 두피가 드러났습니다.",
            "그 누구도 머머리 군단을 막을 수 없었다… 당신도."
        };

        for (const std::string& line : GameOverLines)
        {
            std::cout << "> " << line << "\n";
            Sleep(1500);
        }

        std::cout << "\n머리카락은 모두 빠졌습니다.\n";
        Sleep(1200);
        std::cout << "하지만, 다시 자랄 수도 있습니다...\n";
        Sleep(1500);

        std::cout << "\n당신은 어떻게 하시겠습니까?\n";
        Sleep(1000);

        std::cout << "\n[1] 자라나라 머리머리~!\n";
        std::cout << "[2] 사라져라 머리머리...\n";

        std::cout << "\n입력 >> ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            system("cls");
            std::cout << "\"다시 자라게 하자, 희망.\"\n";
            Sleep(1500);
            GManager->ResetGame(); // 이름 입력부터 재시작
        }
        else
        {
            system("cls");

            std::vector<std::string> ExitLines = {
                "이제... 나도 그들과 같은 빛을 비춘다.",
                "머머리는… 생각보다 나쁘지 않았다.",
                "이젠... 빗도 필요 없다.",
                "머리카락을 잃고, 평온을 얻었다."
            };

            for (const std::string& line : ExitLines)
            {
                std::cout << "\"" << line << "\"\n";
                Sleep(1200);
            }

            std::cout << "\n머머리 연합에 가입하셨습니다. 반짝이는 앞날을 기원합니다.\n";
            exit(0); // 완전 종료
        }
    }

}