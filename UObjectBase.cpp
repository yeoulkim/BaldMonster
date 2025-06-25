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
