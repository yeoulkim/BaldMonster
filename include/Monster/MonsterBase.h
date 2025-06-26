//
// Created by suaio on 2025-06-24.
//

#pragma once
#include <string>
#include <memory>
#include "Item/Item.h"
#include "MonsterDefinition.h"

// 몬스터 클래스
class MonsterBase {
    protected:
        MonsterDefinition def; // 몬스터 정의 구조체
        int Level, CurrentHP, CurrentMP; // 현재 몬스터 상태

    public:
        MonsterBase(MonsterDefinition def, int level); // 몬스터 생성
        virtual ~MonsterBase() = default; // 소명자 default

        std::string GetName() const; // 몬스터 이름 Getter
        int GetHP() const; // 몬스터 HP Getter
        int GetMP() const; // 몬스터 MP Getter
        int GetAttack() const; // 몬스터 공격력 Getter
        void GetDamaged(int dmg); // 몬스터 피해 함수
        std::string GetRandomLines() const; // 랜덤 대사 함수

        virtual void GetTurn(); // 몬스터 턴 사용
        virtual std::unique_ptr<Item> DropItem(); // 몬스터 아이템 드랍

        // 전투 헬퍼 함수 추가
        inline bool IsAlive() const {return CurrentHP > 0;}
};
