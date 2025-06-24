#include "AttackItem.h"
#include "Character.h"
#include <iostream>

AttackItem::AttackItem(std::string InName, int InDamage, std::string InMessage, EAttackEffect InEffectType, int InPrice)
    : Item(InName, InPrice), Damage(InDamage), AcquireMessage(InMessage), EffectType(InEffectType) {
}


void AttackItem::SetTarget(MonsterBase* Target)
{
    TargetEnemy = Target;
}

int AttackItem::Use(Character* User)
{
    if (!User || !TargetEnemy) return 0;

    if (EffectType == EAttackEffect::DirectDamage)
    {
        TargetEnemy->TakeDamage(Damage);
        return Damage; // 입힌 데미지 반환
    }

    return 0;
}

std::string AttackItem::GetName() const
{
    return Name; // 부모 클래스에서 상속받은 Name을 사용
}

std::string AttackItem::GetAcquireMessage() const
{
    return AcquireMessage;
}

int AttackItem::GetPrice() const
{
    return Price; // 부모 클래스에서 상속받은 Price를 사용
}

MonsterBase* AttackItem::GetTargetEnemy() const
{
    return TargetEnemy;
}