#include "AttackItem.h"
#include "Character.h"
#include <iostream>

AttackItem::AttackItem(std::string InName, int InDamage, std::string InMessage, EAttackEffect InEffectType, int InPrice)
    : Item(InName, InPrice), Damage(InDamage), AcquireMessage(InMessage), EffectType(InEffectType) {}

void AttackItem::Use(Character* Target)
{
    if (!Target) return;

    if (EffectType == EAttackEffect::DirectDamage)
    {
        Target->TakeDamage(Damage);
        std::cout << Target->GetName() << "의 두피에 " << Damage << "의 타격을 입혔다! 모근이 흔들린다...\n";
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
