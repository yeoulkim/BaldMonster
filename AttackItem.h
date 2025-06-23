#pragma once

#include "Item.h"
#include "Character.h"

class AttackItem : public Item
{
public:
    AttackItem(std::string InName, int InDamage)
        : Name(InName), Damage(InDamage) {
    }

    virtual void Use(Character* Target) override;
    virtual std::string GetName() const override;

private:
    std::string Name;
    int Damage;
};
