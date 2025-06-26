#pragma once
#include "Character.h"
#include "Item.h"

class Bible : public Item {
public:
    // 이름 반환
    std::string GetName() const override { return "탈모의 성서"; }

    // 사용 대사
    std::string GetAcquireMessage() const override {
        return "...나는 이제 모든 대머리의 힘을 이해했다.";
    }

    // 사용 기능
    void Use(Character* target) override {
        if (target) target-> Heal(50); // 상세효과 나중에 적용
    }
};

