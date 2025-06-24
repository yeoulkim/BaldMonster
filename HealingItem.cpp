#include "HealingItem.h"
#include "Character.h"
#include <iostream>

HealingItem::HealingItem(std::string InName, int InAmount, std::string InMessage, int InPrice)
    : Item(InName, InPrice), HealAmount(InAmount), AcquireMessage(InMessage) {
}

void HealingItem::Use(Character* Target)
{
    if (Target)
    {
        Target->Heal(HealAmount);
        std::cout << Target->GetName() << "의 두피가 촉촉해진다... +" << HealAmount << " 회복!\n";
    }
}

std::string HealingItem::GetName() const
{
    return Name; // 부모 클래스에서 상속받은 Name을 사용
}

std::string HealingItem::GetAcquireMessage() const
{
    return AcquireMessage;
}

int HealingItem::GetPrice() const
{
    return Price; // 부모 클래스에서 상속받은 Price를 사용
}
