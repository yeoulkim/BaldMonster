#pragma once
#include "Item.h"
#include "MonsterBase.h"

enum class EAttackEffect
{
    DirectDamage
};

class AttackItem : public Item
{
public:
    AttackItem(std::string InName, int InDamage, std::string InMessage, EAttackEffect InEffectType, int InPrice);

    int Use(Character* Target) override;
    void SetTarget(MonsterBase* Target); //몬스터 타겟 설정 함수
    std::string GetName() const override;
    std::string GetAcquireMessage() const override;
    int GetPrice() const override;
    MonsterBase* GetTargetEnemy() const;

private:
    int Damage;
    std::string AcquireMessage;
    EAttackEffect EffectType;

    MonsterBase* TargetEnemy = nullptr;
    
};
