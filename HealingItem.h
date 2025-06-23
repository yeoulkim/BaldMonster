#pragma once

#include "Item.h"
#include "Character.h"
#include <string>

class HealingItem : public Item
{
public:
    HealingItem(std::string InName, int InHealAmount)
        : Name(InName), HealAmount(InHealAmount) {
    }

    virtual void Use(Character* Target) override;
    virtual std::string GetName() const override;

private:
    std::string Name;
    int HealAmount;
};
