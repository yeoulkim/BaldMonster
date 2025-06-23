#pragma once

#include <string>

class Character;  // 전방 선언

class Item
{
public:
    virtual void Use(Character* Target) = 0;
    virtual std::string GetName() const = 0;
    virtual ~Item() {}  // 가상 소멸자
};
