#include "GameManager/BattleSystem.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <random>
#include <windows.h>
#include "GameManager/GameManager.h"
#include "Item/AttackItem.h"

#include "BossMonster.h"
#include "MonsterLoader.h"

extern GameManager* GManager;   // GameManager에 접근하기 위해 전역 포인터 사용 -> 배틀시스템 안에서도 ResetGame() 호출 가능

void Dungeon(GameManager* gm);

MonsterBase* GameManager::SummonRandomMonster(int PlayerLevel, int Difficulty) {
    // filesystem으로 폴더 내 경로 찾기
    namespace fs = std::filesystem;

    // assets/data 폴더의 *.json 모으기
    std::vector<fs::path> jsonFiles;

    // 몬스터 난이도 조정
    std::string keyword;
    switch (Difficulty) {
        case 1: keyword = "easy"; break;
        case 2: keyword = "normal"; break;
        case 3: keyword = "hard"; break;
        default: keyword = ""; break;  // 모든 몬스터 가능
    }

    for (auto& entry : fs::directory_iterator("assets/data")){ // 반복자로 경로 찾기
        if (entry.path().extension() == ".json") { // 확정자는?? JSON~
            std::string name = entry.path().stem().string(); // 경로의 찾을 이름
            if (keyword.empty() || name.find(keyword) != std::string::npos) // 키워드 및 이름 확인
                jsonFiles.push_back(entry.path()); // 찾았으면 이모~ 동적배열에 추가요~
        }
    }

    // 해당 경로에 JSON 없으면 던져버리고 RunTime 주자
    if (jsonFiles.empty())
        throw std::runtime_error("assets/data 폴더에 몬스터 JSON이 없습니다!");

    // <random>으로 난수로 하나 선택
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<size_t> dist(0, jsonFiles.size() - 1);
    fs::path picked = jsonFiles[dist(rng)];

    // 정의 로드 (규격대로~) → 객체 생성 (다시 한 번 규격대로~)
    MonsterDefinition def = LoadMonster(picked.string());

    bool isBoss = picked.stem().string().find("boss") != std::string::npos; // 파일명에 boss 포함?
    if (isBoss) {// 너 진영형님이냐 아니냐?
        // std::cout << "[DBG] Boss HP:" << def.HP << '\n';
        return new BossMonster(def, PlayerLevel);
    }
    else {
        // std::cout << "[DBG] Normal HP:" << def.HP << '\n';
        return new MonsterBase(def, PlayerLevel);
    }
}

void BattleSystem::StartBattle(Character* Player, MonsterBase* Enemy, int MaxExperience)
{

        std::cout << "\n[!] 작전 개시. 두피 전장에 진입한다.\n";
        std::cout << "\n[목표 확인] " << Enemy->GetName() << " 등장!\n";
        std::cout << Enemy->GetName() << ": \"" << Enemy->GetRandomLines() << "\"\n";

        while (Player->IsAlive() && Enemy->IsAlive()) {
            std::cout << "\n┌───────────────────── 작전 선택 ─────────────────────┐\n";
            std::cout << "                                                     \n";
            std::cout << "    1. 정수리 맨주먹 공격                                 \n";
            std::cout << "    2. 두피 보존 키트 사용                                \n";
            std::cout << "    3. 전장 후퇴 (도망가기)                               \n";
            std::cout << "                                                     \n";
            std::cout << "└────────────────────────────────────────────────────┘\n";
            std::cout << "명령을 입력하시오 >> ";

            if (std::cin.peek() == '\n') std::cin.ignore();    // 남은 개행 제거

            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            int cmd;

            if (!(ss >> cmd) || !(ss >> std::ws).eof() || cmd < 1 || cmd > 3) {
                std::cout << "[!] 숫자 1~3만 입력하세요.\n";
                continue;
            }

            PlayAction action = static_cast<PlayAction>(cmd);
            // system("cls");

            switch (action){
                case PlayAction::Attack:
                {
                    int DamageToEnemy = Player->GetAttack();
                    Enemy->GetDamaged(DamageToEnemy);
                    std::cout << "[전투 보고] " << Enemy->GetName() << "에게 정수리 공격 성공! 피해량: "
                        << DamageToEnemy << " (잔여 모발: " << Enemy->GetHP() << ")\n";
                    break;
                }
                case PlayAction::UseItem:
                {
                    Player->CheckInventory();
                    std::cout << "\n사용할 두피 보존 키트를 입력하시오 (취소: '취소'):\n>> ";
                    std::string itemName;
                    std::getline(std::cin, itemName);

                    if (itemName != "취소"){
                        for (auto* item : Player->GetInventory()){
                            if (item->GetName() == itemName) {
                                // 공격 아이템이면 몬스터를 타겟으로 설정
                                auto* attackItem = dynamic_cast<AttackItem*>(item);
                                if (attackItem) {
                                    attackItem->SetTarget(Enemy); // 이걸 안 하면 몬스터 안 맞음
                                }
                                break;
                            }
                        }
                        Player->UseItem(itemName);
                        // 아이템 사용 후 적 턴으로 넘어감
                        break;

                    }
                }
                case PlayAction::Run:
                {
                    std::cout << "\n[후퇴 명령] 당신은 전장을 떠났습니다...\n";
                    return;
                }
                default:
                {
                    std::cout << "\n[!] 잘못된 명령입니다. 다시 선택하시오.\n";
                    continue; // 다시 선택
                }
            }

            // system("pause >nul");

            // 몬스터가 죽었는지 체크
            if (!Enemy->IsAlive())
            {
                std::cout << "[V] " << Enemy->GetName() << " 제거 완료.\n";

                int ExpReward = 50;
                int GoldReward = 10 + (rand() % 41);

                Player->GainExperience(ExpReward);
                Player->SetGold(Player->GetGold() + GoldReward);
                std::cout << "[보상] 경험치 +" << ExpReward << " | 자금 +" << GoldReward << " G\n";

                // system("pause >nul");
                return;
            }

            // 적의 턴
            int BeforeHP = Player->GetHealth();
            Player->TakeDamage(Enemy->GetAttack());
            int AfterHP = Player->GetHealth();
            if (BeforeHP == AfterHP)
                std::cout << "[회피] 민첩한 빗질로 공격을 회피! 두피는 무사합니다.\n";
            else
                std::cout << "[피격] 정수리에 직접타! "
                << (BeforeHP - AfterHP) << " 손실 발생 (잔여 모발: " << AfterHP << ")\n";

            // 턴 끝날 때 효과 업데이트
            Player->UpdateTurn();

            // system("pause >nul");
        }

        // 게임 오버 처리, 재시작
        if (Player->GetHealth() <= 0)
        {
            std::cout << "[GAME OVER] " << Player->GetName() << "이(가) 쓰러졌다. 머리카락을 지키지 못했다...\n";
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

            std::cout << "\n숫자를 입력하시오. >> ";
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

void GameManager::StartBossBattle(Character* player)
{
    MonsterDefinition def = LoadMonster("assets/data/boss.monster.json");  // 반드시 존재해야 함
    MonsterBase* boss = new BossMonster(def, player->GetLevel());
    BattleSystem::StartBattle(player, boss, MaxExperience);


    std::cout << "\n...\n";
    Sleep(1000);
    std::cout << "[경고] 비정상적인 탈모 수치 감지\n";
    Sleep(1200);
    std::cout << "[시스템] 모근 안정화 실패. 긴급 프로토콜을 발동합니다...\n";
    Sleep(1200);
    std::cout << "...\n";
    Sleep(800);
    std::cout << "[ALERT] 대규모 반사광 신호 감지됨\n";
    Sleep(1200);
    std::cout << "\n[!] 정체불명의 존재가 접근 중입니다...\n";
    Sleep(1500);
    std::cout << "빛의 강도가 임계치를 초과했습니다. 시야 확보 불가...\n";
    Sleep(1500);
    std::cout << "\n\n\"...진영형님이... 오고 계십니다.\"\n";
    Sleep(2000);
    std::cout << "\n당신은 준비되어 있습니까...? [Y/N]\n";

    char Input;
    std::cin >> Input;
    std::cin.ignore();

    if (Input != 'Y' && Input != 'y')   // 회피 처리
    {
        std::cout << "\n당신은... 아직 그분과 마주할 준비가 되지 않았다.\n";
        Sleep(1200);
        std::cout << "[이탈] 전장을 벗어납니다.\n";
        AddLog("진영형님과의 조우를 회피했다. 모발은 살아남았지만, 자존심은 흔들렸다.");
        return;
    }

    delete boss;
}