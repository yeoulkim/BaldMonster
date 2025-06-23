#pragma once
#include <iostream>
#include <thread>
#include <chrono>

class UObjectBase
{
public:
    UObjectBase();
    virtual ~UObjectBase();

    void Run();  // BeginPlay -> Tick 반복

protected:
    bool bIsTickEnabled;
    float DeltaTime;

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
};
