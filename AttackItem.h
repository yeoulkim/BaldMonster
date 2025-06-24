#pragma once
#include "Item.h"

enum class EAttackEffect
{
    DirectDamage
};

class AttackItem : public Item
{
public:
    AttackItem(std::string InName, int InDamage, std::string InMessage, EAttackEffect InEffectType, int InPrice);

    void Use(Character* Target) override;
    std::string GetName() const override;
    std::string GetAcquireMessage() const override;
    int GetPrice() const override;

private:
    int Damage;
    std::string AcquireMessage;
    EAttackEffect EffectType;
    int Price;
};
