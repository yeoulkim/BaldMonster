#include "GameManager/GameManager.h"

#include <algorithm>
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <filesystem>

#include "BattleSystem.h"
#include "Monster/BossMonster.h"
#include "Item/Item.h"
#include "Item/AttackItem.h"
#include "Item/HealingItem.h"
#include "Save/SaveManager.h"
#include "Shop/Shop.h"

namespace fs = std::filesystem;

GameManager::GameManager()
{
    bIsFirstPlay = true;
    bIsTickEnabled = true;
    Player = nullptr;
}

GameManager::~GameManager()
{
    delete Player;
}

void Intro()
{
    std::cout << "\n\n";
    std::cout << "2099년…\n\n";
    Sleep(1000);

    std::cout << "인류의 머리카락은… 사라졌다.\n\n";
    Sleep(1200);

    std::cout << "탈모 바이러스 \"B-ald 99\"의 확산\n";
    Sleep(600);

    std::cout << "사람들의 머리는 하나둘씩 반짝이기 시작했고\n";
    Sleep(900);

    std::cout << "그 반짝임은… 곧 공포가 되었다.\n\n";
    Sleep(1200);

    std::cout << "그리고 그 틈을 타,\n";
    Sleep(600);

    std::cout << "어디선가 나타난 정체불명의 존재들…\n";
    Sleep(1300);

    std::cout << "\n\n";
    Sleep(800);

    std::cout << "> \"...난 아직 탈모약을 믿는다.\"\n\n";
    Sleep(1000);

    std::cout << "> \"머리카락을 되찾기 위해, 난 그들을 벗겨버릴 것이다.\"\n\n";
    Sleep(1300);

    std::cout << "> \"난 마지막 모발 보유자다…\n";
    std::cout << "내 머리를 건들면… 가만 안 둬.\"\n\n";
    Sleep(1400);

    std::cout << "지금,\n\n";
    Sleep(700);

    std::cout << "머머리 군단에 맞서는\n\n";
    Sleep(800);

    std::cout << "최후의 모발 전쟁이 시작된다.\n\n";
    Sleep(1500);

    std::cout << "========================================\n";
    std::cout << "\n\n";


    char Input;

    while (true)
    {
        std::cout << "머리카락을 걸고 싸우시겠습니까? [Y/N]: ";
        std::cin >> Input;
        std::cin.ignore();

        if (Input == 'Y' || Input == 'y')
        {
            std::cout << "\n모근을 다잡고, 전장으로 나아갑니다...\n";
            Sleep(1500);
            break;
        }
        else if (Input == 'N' || Input == 'n')
        {
            std::cout << "\n당신은... 민둥산의 길을 택했습니다.\n";
            Sleep(1500);
            std::cout << "이제, 당신도 머머리입니다.\n";
            Sleep(1500);
            exit(0);
        }
        else
        {
            std::cout << "잘못된 입력입니다. Y 또는 N을 입력하세요.\n";
        }
    }
}

void GameManager::BeginPlay()
{
    if (bIsFirstPlay)   // bIsFristPlay가 true인 경우에만 Intro() 호출
    {
        Intro();
        bIsFirstPlay = false;
    }

    // 저장될 폴더가 없는 경우 생성
    fs::create_directory(fs::path("save"));

    // 저장목록 수집할 배열
    std::vector<std::string> slot;
    for (auto& e : fs::directory_iterator("save")) // 반복자로 save 경로 찾기
        if (e.path().extension() == ".json") // 확장자 JSON 췍
            slot.push_back(e.path().stem().string()); // 배열에 확장자 없는 이름 추가

    if (!slot.empty()){
        std::cout << "\n 저장된 게임\n";
        for (size_t i = 0; i < slot.size(); ++i)
            std::cout << " " << i + 1 << ") " << slot[i] << '\n';
        std::cout << " 0) 새 게임\n";

        int sel = -1;
        while (true){
            std::cout << "\n번호를 입력 >> ";
            if (!(std::cin >> sel)) {           // 숫자 아닌 입력 필터
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // 새게임
            if (sel == 0) break;
            if (1 <= sel && sel <= (int)slot.size()){
                std::string file = slot[sel-1];
                file.erase(std::remove_if(file.begin(), file.end(), ::isspace), file.end());

                // 빈 캐릭터
                if (!Player) Player = new Character();
                if (SaveManager::LoadGame(Player, slot[sel-1]))
                {
                    std::cout << "[✔] 로드 완료!\n";
                    AddLog("저장된 게임을 불러왔습니다.");
                    DisplayStatus(1);
                    return; // 로드 성공 → 바로 게임 진행
                }
                std::cout << "[X] 로드 실패, 새 게임으로.\n";
                break; // 실패 → 새 게임
            }
            std::cout << "잘못된 번호입니다.\n";
        }
    }

    /* ---- 여기서부터는 새 게임 ---- */
    std::srand((unsigned)std::time(nullptr));

    std::string name;
    std::cout << "\n===== [ 대머리 사냥꾼 등록소 ] =====\n";
    std::cout << "머리카락 보유자여, 이름을 남기시오: ";
    std::getline(std::cin, name);

    if (name.empty()) name = "익명 두피";
    CreateCharacter(name);
    AddLog("등록 완료. 당신은 이제 머리카락을 지킬 준비가 되었다.");
    DisplayStatus(1);

}


void GameManager::Tick(float DeltaTime)
{
    if (Player == nullptr || Player->GetHealth() <= 0 || Player->GetLevel() >= MaxLevel)
    {
        bIsTickEnabled = false;
        // EndGame();
        return;
    }
    std::cout << "\x1B[36m";
    std::cout << "\n[O] 당신의 모근은 아직 버티고 있다.\n";
    std::cout << "다음 작전을 선택한다.\n";
    std::cout << "----------------------------------------\n";
    std::cout << "[1] 대머리 군단과 교전한다.\n";
    std::cout << "[2] 탈모약 상점에 방문한다.\n";
    std::cout << "[3] 남아 있는 모발 상태를 진단한다.\n";
    std::cout << "[4] 두피 생존 키트 확인\n";
    std::cout << "[5] 전장을 떠나 대머리의 길을 걷는다.\n";
    std::cout << "----------------------------------------\n";
    std::cout << "입력 >> ";
    std::cout << "\x1B[0m";

    int Choice;
    std::cin >> Choice;
    std::cin.ignore();

    switch (Choice)
    {
    case 1:
        std::cout << "[!] 작전 선택 완료. 곧 던전 정보가 표시됩니다...\n";
        Sleep(1000); // 대기 후 자연스러운 입장
        DungeonMenu(Player);
        break;
    case 2:
        VisitShop();
        break;
    case 3:
        DisplayStatus(1);
        break;
    case 4:
        Player->CheckInventory();  // 4번: 인벤토리 확인
        break;
    case 5:
        std::cout << "\n[안내] 전장을 떠나기 전, 현재 진행 상황을 저장합니다...\n";

        if (Player) {
            std::string fileName = Player->GetName();
            // 공백 제거 (파일명에 공백 있으면 위험하니까)
            fileName.erase(std::remove_if(fileName.begin(), fileName.end(), ::isspace), fileName.end());

            if (SaveManager::SaveGame(Player, fileName)) {
                std::cout << "[✔] 저장 완료! 파일명: " << fileName << ".json\n";
            } else {
                std::cout << "[X] 저장 실패. 게임 데이터를 잃을 수 있습니다.\n";
            }
        }

        bIsTickEnabled = false;
        std::cout << "\n당신은 도약 대신 후퇴를 택했다. 두피는 침묵했다.\n";
        ShowGameLog("탈주 감지. 기록: '머리를 지키기엔 용기가 부족했다.'");
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

// 재시작
void GameManager::ResetGame()
{
    delete Player;
    Player = nullptr;
    bIsTickEnabled = true;

    BeginPlay(); // 이름 입력부터 다시
}

void GameManager::CreateCharacter(std::string Name)
{
    Player = new Character(Name, 200, 20, 1);  // ✅ 예시값 넣어줌
    //Player->SetHealth(100);
    Player->SetLevel(1);
    Player->SetExperience(0);
    Player->SetGold(0);
}

void GameManager::DungeonMenu(Character* player)
{
    // 플레이어 레벨 가져오기
    int lv = player->GetLevel();

    // 각 레벨당 던전 입장
    auto valid = [&](int opt){
        if (lv >= 10) return opt == 4 || opt == 5;                // 10레벨↑ : 보스 던전만
        if (lv >= 8)  return opt == 3 || opt == 5;                // 8~9     : 고급 던전
        if (lv >= 4)  return opt == 2 || opt == 5;                // 4~7     : 중급 던전
        return opt == 1 || opt == 5;                              // 1~3     : 초보 던전
    };

    while (true) {
        system("cls");
        std::cin.clear();
        std::cout << "\n[탈모 방패] 반짝임으로부터 잠시 회피합니다. 엔터를 눌러 계속.\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout <<
                    "\n====== 입장 가능 던전 ======\n"
                    "   1) 반짝이는 사막   (LV 1~3)    \n"
                    "   2) 황폐한 늪   (LV 4~7)       \n"
                    "   3) 어두운 동굴   (LV 8~9)      \n"
                    "   4) 지하 대성전 (보스)  (LV 10)  \n"
                    "   5) 다시 생각하기(돌아가기)      \n"
                    "==========================\n";

        std::cout << "\n입장할 던전 번호 입력 >> ";
        std::string line;  std::getline(std::cin, line);
        std::stringstream ss(line);

        int sel;
        if (!(ss >> sel) || !(ss >> std::ws).eof() || sel < 1 || sel > 5) continue;
        if (!valid(sel)) { std::cout << "입장 조건이 맞지 않습니다!\n"; Sleep(1000); continue; }

        if (sel == 5) {
            std::cout << "\n[안내] 던전 선택을 취소하고 메인 메뉴로 돌아갑니다.\n";
            Sleep(1000);
            return;
        }

        if (sel == 4)      StartBossBattle(player);
        else               StartRandomBattle(player, sel);  // 난이도별 몬스터 풀
        return;
    }
}

void GameManager::DisplayStatus(int Level)
{
    std::ostringstream oss;

    std::string name = Player->GetName();
    std::string level = "Lv." + std::to_string(Player->GetLevel());
    std::string hp = std::to_string(Player->GetHealth()) + " / " + std::to_string(Player->GetMaxHealth());
    std::string exp = std::to_string(Player->GetExperience()) + " / " + std::to_string(MaxExperience);
    std::string gold = std::to_string(Player->GetGold()) + " G";

    std::cout << "\n┌───────────────────── 두피 상태 리포트 ─────────────────────┐\n";
    std::cout << "    코드네임        : " << std::left << std::setw(40) << name << " \n";
    std::cout << "    성장 등급       : " << std::left << std::setw(40) << level << "\n";
    std::cout << "    두피 내구도     : " << std::left << std::setw(40) << hp << "   \n";
    std::cout << "    모근 경험치     : " << std::left << std::setw(40) << exp << "  \n";
    std::cout << "    확보 자금       : " << std::left << std::setw(40) << gold << " \n";
    std::cout << "└──────────────────────────────────────────────────────────┘\n";
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

void GameManager::StartRandomBattle(Character* Player, int Difficulty)
{

    std::cout << "[DBG] 난이도 선택 " << Difficulty << "\n";
    std::cout << "[DBG] StartRandomBattle() 진입\n";

    MonsterBase* Enemy = SummonRandomMonster(Player->GetLevel(), Difficulty);  // 여기서 생성
    if (!Enemy) {
        std::cerr << "[ERR] Enemy 생성 실패!\n";
        return;
    }

    std::cout << "[DBG] Enemy 생성됨: " << Enemy->GetName()
              << ", HP:" << Enemy->GetHP() << '\n';

    BattleSystem::StartBattle(Player, Enemy, MaxExperience);
    delete Enemy;
}

void GameManager::VisitShop()
{
    Shop shop;
    shop.EnterShop( Player);
}