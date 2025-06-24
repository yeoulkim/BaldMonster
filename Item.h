#pragma once
#include <string>

class Character;

enum class EItemSource
{
    MonsterDrop,
    ShopPurchase,
    QuestReward
};

class Item
{
public:
    Item();
    Item(const std::string& InName, int InPrice);

    virtual ~Item() {}

    virtual void Use(Character* Target) = 0;
    virtual std::string GetName() const = 0;
    virtual std::string GetAcquireMessage() const = 0;

    void SetSource(EItemSource InSource);
    EItemSource GetSource() const;

    virtual int GetPrice() const;

protected:
    std::string Name;
    EItemSource Source;
    int Price;
};
