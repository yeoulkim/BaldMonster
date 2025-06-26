#pragma once

#include <vector>
#include "Item/Item.h"
#include "Character/Character.h"

class Shop
{
public:
    void EnterShop(Character* Player);
    
private:
    void ShowBuyMenu(Character* Player);

    void ShowBuyAttackMenu(Character *Player);

    void ShowSellMenu(Character* Player);
    std::vector<Item*> GetHealingItems();
    std::vector<Item*> GetAttackItems();
};