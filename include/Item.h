#pragma once
#include <string>

class Item {
public:
    virtual ~Item() = default;
    virtual std::string GetName() const = 0;
};
