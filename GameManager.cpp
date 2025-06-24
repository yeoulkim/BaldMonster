#include "GameManager.h"
#include "BossMonster.h"
#include "YellowMonster.h"
#include "Item.h"
#include "AttackItem.h"
#include "HealingItem.h"

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdlib>

GameManager::GameManager()
{
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

    std::srand(static_cast<unsigned int>(std::time(0)));

    std::cout << "\n===== [ 대머리 사냥꾼 등록소 ] =====\n";
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
        StartRandomBattle(Player);
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


void GameManager::DisplayStatus(int Level)
{
    std::ostringstream oss;

    std::string name = Player->GetName();
    std::string level = "Lv." + std::to_string(Player->GetLevel());
    std::string hp = std::to_string(Player->GetHealth()) + " / " + std::to_string(Player->GetMaxHealth());
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

void GameManager::StartRandomBattle(Character* Player)
{
    MonsterBase* Enemy = nullptr;
    int Level = Player->GetLevel();


    if (Level >= 10)
    {
        std::cout << "\n...\n";
        Sleep(1000);
        std::cout << "[경고] 비정상적인 탈모 수치 감지\n";
        Sleep(1200);
        std::cout << "[시스템] 모근 안정화 불가. 긴급 프로토콜 활성화\n";
        Sleep(1200);
        std::cout << "...\n";
        Sleep(800);
        std::cout << "[ALERT] 대규모 반사광 신호 감지됨\n";
        Sleep(1200);
        std::cout << "\n[!]  정체불명의 존재가 접근 중입니다...\n";
        Sleep(1500);
        std::cout << "빛의 강도가 일정 수치를 넘었습니다. 시야 확보 불가...\n";
        Sleep(1500);
        std::cout << "\n\n\"...진영형님이... 오고 계십니다.\"\n";
        Sleep(2000);
        std::cout << "\n당신은 준비되어 있습니까...?\n";

        char Input;
        std::cin >> Input;
        std::cin.ignore();

        if (Input != 'Y' && Input != 'y')
        {
            std::cout << "\n당신은... 아직 그분과 마주할 준비가 되지 않았다.\n";
            Sleep(1200);
            std::cout << "[*] 전장에서 물러났습니다.\n";
            AddLog("진영형님과의 조우를 회피했다.");
            return; // 전투 시작 없이 함수 종료
        }

        Enemy = new BossMonster(Level);
    }
    else
        Enemy = new YellowMonster(Level); // 예시 몬스터

    BattleSystem::StartBattle(Player, Enemy, MaxExperience);
    delete Enemy;
}

// 4번 선택지로 수정
//void GameManager::EndGame()
//{
//    std::cout << "\n당신은 도약 대신 후퇴를 택했다. 두피는 침묵했다.\n"; 
//    ShowGameLog("탈주 감지. 기록: '머리를 지키기엔 용기가 부족했다.'");
//}

// 틀 맞추기
void GameManager::VisitShop()
{
    int Choice;
    std::cout << "\n┌───────────  탈모약 상점  ──────────┐\n";
    std::cout << "│  보유 골드: " << std::right << std::setw(5) << Player->GetGold() << " G                │\n";
    std::cout << "├────────────────────────────────────┤\n";
    std::cout << "│  1. 두피를 회복시킬 탈모약         │\n";
    std::cout << "│  2. 두피 강화할 공격 아이템        │\n";
    std::cout << "│  0. 상점 나가기                    │\n";
    std::cout << "└────────────────────────────────────┘\n";  

    std::cout << "아이템을 선택하세요 >> ";
    std::cin >> Choice;
    std::cin.ignore();

    if (Choice == 0)
    {
        AddLog("상점에서 물러났다.");
        return;  // 상점 나가기
    }
    else if (Choice == 1)
    {
        std::vector<Item*> HealingItems = GetHealingShopItems();  // 힐링 아이템 가져오기
        ShowShopItems(HealingItems);
    }
    else if (Choice == 2)
    {
        std::vector<Item*> AttackItems = GetAttackShopItems();  // 공격 아이템 가져오기
        ShowShopItems(AttackItems);
    }
    else
    {
        std::cout << "잘못된 입력입니다.\n";
    }
}

void GameManager::ShowShopItems(const std::vector<Item*>& ShopItems)
{
    std::cout << "\n┌─────────────  아이템 목록  ─────────────┐\n";
    for (size_t i = 0; i < ShopItems.size(); ++i)
    {
        std::cout << "│  " << i + 1 << ". " << std::left << std::setw(15) << ShopItems[i]->GetName()
            << " - 가격: " << std::right << std::setw(5) << ShopItems[i]->GetPrice() << " G     │\n";
    }
    std::cout << "└─────────────────────────────────────────┘\n";
    std::cout << "0. 상점 나가기\n";
    std::cout << "구매할 아이템 번호를 입력하세요 >> ";

    int Choice;
    std::cin >> Choice;
    std::cin.ignore();

    if (Choice == 0)
    {
        AddLog("상점에서 물러났다.");
        return;  // 상점 나가기
    }
    else if (Choice >= 1 && Choice <= static_cast<int>(ShopItems.size()))
    {
        int Price = ShopItems[Choice - 1]->GetPrice();  // 가격 반영

        if (Player->GetGold() >= Price)
        {
            Item* SelectedItem = ShopItems[Choice - 1];
            Player->SetGold(Player->GetGold() - Price);
            Player->AddItem(SelectedItem);

            AddLog(SelectedItem->GetName() + "을(를) 구매했습니다.");
        }
        else
        {
            AddLog("골드가 부족하여 아이템을 구매하지 못했습니다.");
        }
    }
    else
    {
        std::cout << "잘못된 입력입니다.\n";
    }
}

std::vector<Item*> GameManager::GetHealingShopItems()
{
    std::vector<Item*> HealingItems;

    HealingItems.push_back(new HealingItem("싸구려 탈모약", 20, "정수리에 소독약 느낌... 효과는 별로 없는 것 같다.", 30));
    HealingItems.push_back(new HealingItem("보통의 탈모약", 50, "약국에서도 파는 그냥저냥 무난한 탈모약. 이걸로 버틸 수 있을까...", 60));
    HealingItems.push_back(new HealingItem("프리미엄 탈모약", 100, "모근이 감동받아 일어섰다. 광택이 돌아온다.", 100));

    return HealingItems;
}


std::vector<Item*> GameManager::GetAttackShopItems()
{
    std::vector<Item*> AttackItems;

    AttackItems.push_back(new AttackItem("모근 브러시", 10, "정수리를 정돈했다. 명중률이 올라간다!", EAttackEffect::DirectDamage, 30));
    AttackItems.push_back(new AttackItem("전투용 탈모약", 30, "부작용으로 분노가 치솟았다!", EAttackEffect::DirectDamage, 60));

    return AttackItems;
}





