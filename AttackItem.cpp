#include "AttackItem.h"
#include <iostream>

using namespace std;

void AttackItem::Use(Character* Target)
{
    cout << Name << " ���! ��뿡�� " << Damage << " ���ظ� �������ϴ�!" << endl;
    Target->TakeDamage(Damage);
}

string AttackItem::GetName() const
{
    return Name;
}
