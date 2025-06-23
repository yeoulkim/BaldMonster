#include "AttackItem.h"
#include <iostream>

using namespace std;

void AttackItem::Use(Character* Target)
{
    cout << Name << " 사용! 상대에게 " << Damage << " 피해를 입혔습니다!" << endl;
    Target->TakeDamage(Damage);
}

string AttackItem::GetName() const
{
    return Name;
}
