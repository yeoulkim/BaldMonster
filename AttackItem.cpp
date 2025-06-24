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

void AttackItem::Use(Character* User)
{
    if (!User || !TargetEnemy) return;

    if (EffectType == EAttackEffect::DirectDamage)
    {
        TargetEnemy->TakeDamage(Damage);
        // 타겟 이름을 가져와서 출력
        std::string targetName = TargetEnemy->GetName();  // GetName을 사용해서 타겟 이름 가져오기
        std::cout << "[아이템 공격] " << targetName << "에게 " << Damage << " 피해를 입혔다!\n";
    }
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