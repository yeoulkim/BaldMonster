#include "HealingItem.h"
#include <iostream>

void HealingItem::Use(Character* Target)
{
    std::cout << Name << " »ç¿ë!" << std::endl;
    Target->SetHealth(Target->GetHealth() + HealAmount);
}

std::string HealingItem::GetName() const
{
    return Name;
}
