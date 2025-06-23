#include "BattleSystem.h"
#include "GameManager.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

extern GameManager* GManager;   // GameManager�� �����ϱ� ���� ���� ������ ��� -> ��Ʋ�ý��� �ȿ����� ResetGame() ȣ�� ����

void BattleSystem::StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience)
{
    std::cout << "\n[!] ���� ����. ���� ���忡 �����Ѵ�.\n";
    std::cout << ">> ��ǥ �ĺ�: " << Enemy->GetName() << "\n";
    std::cout << Enemy->GetName() << ": \"" << Enemy->GetRandomLine() << "\"\n";
    system("pause >nul");
    while (Player->GetHealth() > 0 && Enemy->GetHealth() > 0)
    {
        int DamageToEnemy = Player->GetAttack();
        Enemy->TakeDamage(DamageToEnemy);
        std::cout << "[����] " << Enemy->GetName() << "���� " << DamageToEnemy
            << " ���ظ� ������. (���� ü��: " << Enemy->GetHealth() << ")\n";
        system("pause >nul");
        if (Enemy->GetHealth() <= 0)
        {
            std::cout << "[V] " << Enemy->GetName() << " ���� �Ϸ�.\n";
            int ExpReward = 20;
            int GoldReward = 10 + (rand() % 41);
            int NewExp = Player->GetExperience() + ExpReward;
            Player->SetExperience(NewExp);
            Player->SetGold(Player->GetGold() + GoldReward);
            std::cout << "[����] ��� ����ġ +" << ExpReward << " | �ڱ� +" << GoldReward << " G\n";
            if (NewExp >= MaxExperience)
            {
                Player->SetExperience(0);
                Player->SetLevel(Player->GetLevel() + 1);
                Player->SetHealth(200);
                std::cout << "[��] ������! ���� ����: " << Player->GetLevel() << "\n";
                std::cout << "[=] ����� ���ǰ� ���� �� �ܴ�������.\n";
                system("pause >nul");
            }
            return;
        }
        int BeforeHP = Player->GetHealth();
        Player->TakeDamage(Enemy->GetAttack());
        int AfterHP = Player->GetHealth();
        if (BeforeHP == AfterHP)
            std::cout << "[ȸ��] ��ø�� ������ ������ ���ߴ�.\n";
        else
            std::cout << "[����] " << (BeforeHP - AfterHP)
            << " ������ ����. (�ܿ� ü��: " << AfterHP << ")\n";
        system("pause >nul");
    }

    // ���� ���� ó��, �����
    if (Player->GetHealth() <= 0)
    {
        std::cout << "[GAME OVER] ����� ��������. �Ӹ�ī���� ��Ű�� ���ߴ�...\n";
        Sleep(1000);

        std::vector<std::string> GameOverLines = {
            "�ӸӸ� ������ ��¦�� �տ��� �ᱹ ���� ���Ҵ�.",
            "����� ���ǰ� �巯�����ϴ�.",
            "�� ������ �ӸӸ� ������ ���� �� �����١� ��ŵ�."
        };

        for (const std::string& line : GameOverLines)
        {
            std::cout << "> " << line << "\n";
            Sleep(1500);
        }

        std::cout << "\n�Ӹ�ī���� ��� �������ϴ�.\n";
        Sleep(1200);
        std::cout << "������, �ٽ� �ڶ� ���� �ֽ��ϴ�...\n";
        Sleep(1500);

        std::cout << "\n����� ��� �Ͻðڽ��ϱ�?\n";
        Sleep(1000);

        std::cout << "\n[1] �ڶ󳪶� �Ӹ��Ӹ�~!\n";
        std::cout << "[2] ������� �Ӹ��Ӹ�...\n";

        std::cout << "\n�Է� >> ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            system("cls");
            std::cout << "\"�ٽ� �ڶ�� ����, ���.\"\n";
            Sleep(1500);
            GManager->ResetGame(); // �̸� �Էº��� �����
        }
        else
        {
            system("cls");

            std::vector<std::string> ExitLines = {
                "����... ���� �׵�� ���� ���� �����.",
                "�ӸӸ��¡� �������� ������ �ʾҴ�.",
                "����... ���� �ʿ� ����.",
                "�Ӹ�ī���� �Ұ�, ����� �����."
            };

            for (const std::string& line : ExitLines)
            {
                std::cout << "\"" << line << "\"\n";
                Sleep(1200);
            }

            std::cout << "\n�ӸӸ� ���տ� �����ϼ̽��ϴ�. ��¦�̴� �ճ��� ����մϴ�.\n";
            exit(0); // ���� ����
        }
    }

}