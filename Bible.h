#pragma once
#include "Item.h"

class Bible : public Item {
public:
    std::string GetName() const override { return "탈모의 성서"; }
};
