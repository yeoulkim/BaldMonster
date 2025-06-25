#pragma once
#include "Item.h"

class Brush : public Item {
public:
    std::string GetName() const override { return "고대의 빗"; }
};
