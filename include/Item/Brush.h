#pragma once
#include "Item.h"

class Brush : public Item {
public:
    // 이름 반환
    std::string GetName() const override { return "고대의 빗"; }

    // 사용 대사
    std::string GetAcquireMessage() const override {
        return "광택이 달라졌다. 이제 진심이다";
    }

    //사용 기능
    void Use(Character* target) override {
        if (target) target-> SetAttackBoost(50); // 상세효과 나중에 적용
    }
};

