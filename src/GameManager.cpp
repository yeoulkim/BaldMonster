#include "GameManager.h"
#include <cstdlib>  // rand(), srand()
#include <ctime>   // time() for random seed
#include <iostream> 

using namespace std;

void GameManager::startGame() 
{
    cout << "===== 대머리 나라에 오신 걸 환영합니다! =====\n";
    string name;
    cout << "캐릭터 이름을 입력하세요: ";
    getline(cin, name);

    CreateCharacter(name);
    AddLog("캐릭터 생성 완료.");

    DisplayStatus(1);  // 시작 레벨 1

    // 이후 GameLoop 등 호출 가능
}   

void GameManager::endGame() 
{
    cout << "게임을 종료합니다. 감사합니다!\n";
    cout << "최종 결과:\n";
    cout << "플레이어 이름: " << Player->getName() << "\n";
    cout << "최종 레벨: " << Player->getLevel() << "\n";
    cout << "총 경험치: " << Player->getExperience() << "\n";
    cout << "총 골드: " << Gold << "\n";
    cout << "게임 종료!\n";
}


void GameManager::CreateCharacter(string Name) 
{
    Player = new Character(Name, 1, 200, 30, 0);  // 이름, 레벨 1, 체력 200, 공격력 30, 경험치 0
    cout << "환영합니다, " << Name << " 님!\n";
}

void GameManager::DisplayStatus(int Level) 
{
    cout << "===== 현재 상태 =====\n";
    cout << "이름: " << Player->getName() << "\n";
    cout << "레벨: " << Player->getLevel() << "\n";
    cout << "체력: " << Player->getHealth() << "/" << Player->getMaxHealth() << "\n";
    cout << "공격력: " << Player->getAttack() << "\n";
    cout << "경험치: " << Player->getExperience() << "/" << MaxExperience << "\n";
    cout << "골드: " << Gold << "\n";
    cout << "=====================\n";
}

void GameManager::AddLog(string Message) 
{
    GameLog.push_back(Message);
    cout << "로그 추가: " << Message << "\n";
}

void GameManager::GameLoop() 
{
    // 게임 루프 로직 구현
    // 예: 몬스터 생성, 전투, 레벨업 등
    cout << "게임 루프 시작...\n";
    while (Player->getLevel < MaxLevel) 
    {
        Monster* enemy = GenerateMonster(Player->getlevel);
        Battle(enemy, Player);
        if (Player->getHealth() <= 0) 
        {
            cout << "게임 오버!\n";
            break;
        }
        LevelUp();
    }
    endGame();
}

void GameManager::LevelUp() 
{
    // 최대 레벨 10으로 제한
    if (Player->getLevel() >= 10) 
    {
        cout << "최대 레벨에 도달했습니다! 현재 레벨: " << Player->getLevel() << "\n";
        return;  // 레벨업을 더 이상 진행하지 않음
    }

    // 경험치가 충분할 경우 레벨업 처리
    if (Player->getExperience() >= MaxExperience) 
    {
        // 레벨 상승
        Player->setLevel(Player->getLevel() + 1);

        // 체력과 공격력 증가
        Player->setHealth(Player->getHealth() + (Player->getLevel() * 20));  // 레벨 × 20만큼 체력 증가
        Player->setAttack(Player->getAttack() + (Player->getLevel() * 5));   // 레벨 × 5만큼 공격력 증가

        // 체력은 최대 체력으로 회복
        Player->setHealth(Player->getMaxHealth());  // 최대 체력으로 회복

        // 경험치 초기화
        Player->setExperience(0);

        // 다음 레벨업을 위한 경험치 증가
        MaxExperience += 50;  // 예시로 레벨업에 필요한 경험치 증가

        cout << "레벨 업! 현재 레벨: " << Player->getLevel() << "\n";
        cout << "체력: " << Player->getHealth() << "/" << Player->getMaxHealth() << "\n";
        cout << "공격력: " << Player->getAttack() << "\n";
    }
}

Monster* GameManager::GenerateMonster(int Level) 
{
    // 몬스터 생성 로직
    cout << "레벨 " << Level << " 몬스터 생성!\n";
    return new Monster(Level * 10, Level * 5);  // 예시: 레벨에 따라 체력과 공격력 설정
}

BossMonster* GameManager::GenerateBossMonster(int Level) 
{
    // 보스 몬스터 생성 로직
    cout << "레벨 " << Level << " 보스 몬스터 생성!\n";
    return new BossMonster(Level * 20, Level * 10);  // 예시: 레벨에 따라 체력과 공격력 설정
}

void GameManager::StartRandomBattle(Character* Player) 
{
    srand((unsigned int)time(0));  // 랜덤 시드 설정
    
    // 보스 몬스터 전투 조건: 플레이어 레벨이 10 이상일 때만 보스 몬스터가 출몰
    if (Player->getLevel() >= 10) 
    {
        // 보스 몬스터 생성
        Monster* bossMonster = GenerateBossMonster(Player->getLevel());
        cout << "보스 몬스터가 출몰했습니다!\n";

        // 보스 몬스터와 전투 시작
        Battle(bossMonster, Player);

        // 보스 몬스터 전투 후 메모리 해제
        delete bossMonster;
        
        // 보스 몬스터 전투 후 게임 종료
        cout << "보스 몬스터 처치! 게임 종료.\n";
        return;
    }
    
    // 5개의 일반 몬스터 생성 (레벨 10 미만일 때만)
    Monster* monsters[5];
    for (int i = 0; i < 5; ++i) 
    {
        monsters[i] = GenerateMonster(Player->getLevel());  // 일반 몬스터 생성
    }

    // 랜덤으로 1개의 일반 몬스터 선택 (5개 일반 몬스터 중 하나)
    int randNum = rand() % 5;  // 0~4 사이의 랜덤 숫자
    Monster* chosenMonster = monsters[randNum];

    // 선택된 일반 몬스터와 전투 시작
    Battle(chosenMonster, Player);

    // 전투 후 선택된 몬스터 메모리 해제
    delete chosenMonster;

    // 만약 전투 후 경험치가 100 이상이면 레벨업 처리
    if (Player->getExperience() >= 100) 
    {
        LevelUp();  // 자동 레벨업
    }
}

void GameManager::Battle(Monster* Enemy, Character* Player)
{
    cout << "전투 시작! 적: " << Enemy->getHealth() << " 체력\n";
    
    // 랜덤 골드 획득 (전투 승리 시 10~20 골드)
    int earnedGold = rand() % 11 + 10; // 10~20 사이 랜덤

    // 턴제 전투 시작
    while (Enemy->getHealth() > 0 && Player->getHealth() > 0) 
    {
        // 플레이어 공격
        Enemy->takeDamage(Player->getAttack());
        cout << "플레이어가 적에게 " << Player->getAttack() << " 데미지를 입혔습니다.\n";
        if (Enemy->getHealth() <= 0) 
        {
            cout << "적을 처치했습니다!\n";
            Experience += 50;  // 경험치 50 획득
            Gold += earnedGold;  // 전투에서 획득한 골드 추가
            AddLog("적을 처치했습니다.");
            break;
        }

        // 적 공격
        Player->takeDamage(Enemy->getAttack());
        cout << "적이 플레이어에게 " << Enemy->getAttack() << " 데미지를 입혔습니다.\n";
        if (Player->getHealth() <= 0) 
        {
            cout << "플레이어가 쓰러졌습니다!\n";
            AddLog("플레이어가 쓰러졌습니다.");
            break;
        }
    }
    
    // 전투 후 경험치가 100 이상이면 자동 레벨업
    if (Player->getExperience() >= 100) 
    {
        LevelUp();  // 경험치가 100 이상이면 자동으로 레벨업
    }

    // 몬스터 메모리 해제는 Battle 함수 내에서 처리됨
}

void GameManager::VisitShop() 
{
    cout << "상점에 방문했습니다.\n";
    // 상점 로직 구현
    // 예: 아이템 구매, 판매 등
}

void GameManager::DisplayInventory(Character* Player) 
{
    cout << "===== 인벤토리 =====\n";
    // 인벤토리 아이템 출력 로직
    // 예: Player->getInventory() 등을 통해 아이템 목록 출력
    cout << "인벤토리 크기: " << InventorySize << "\n";
    cout << "=====================\n";
}

void GameManager::ShowGameLog(string Message) 
{
    cout << "게임 로그: " << Message << "\n";
    // 게임 로그 출력 로직
    // 예: GameLog 벡터의 내용을 출력
}

void GameManager::AddLog(string Message) 
{
    GameLog.push_back(Message);
    cout << "로그 추가: " << Message << "\n";
}

GameManager::GameManager() 
{
    cout << "게임 매니저 초기화...\n";
    // 초기화 로직
}

GameManager::~GameManager() 
{
    cout << "게임 매니저 종료...\n";
    delete Player;  // Player 메모리 해제
    delete GameShop;  // GameShop 메모리 해제
    // 추가적인 메모리 해제 로직 필요 시 구현
}

