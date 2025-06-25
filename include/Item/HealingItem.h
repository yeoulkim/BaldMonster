#pragma once
#include "Item.h"

class HealingItem : public Item
{
public:
    HealingItem(std::string InName, int InAmount, std::string InMessage, int InPrice);

    void Use(Character* Target) override;
    std::string GetName() const override;
    std::string GetAcquireMessage() const override;
    int GetPrice() const override;

private:
    int HealAmount;
    std::string AcquireMessage;
};
