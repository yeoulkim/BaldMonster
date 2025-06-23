#include "HealingItem.h"
#include <iostream>

void HealingItem::Use(Character* Target)
{
    std::cout << Name << " 사용!" << std::endl;
    Target->SetHealth(Target->GetHealth() + HealAmount);
}

std::string HealingItem::GetName() const
{
    return Name;
}
