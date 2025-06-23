#pragma once

#include <string>

class Character;  // ���� ����

class Item
{
public:
    virtual void Use(Character* Target) = 0;
    virtual std::string GetName() const = 0;
    virtual ~Item() {}  // ���� �Ҹ���
};
