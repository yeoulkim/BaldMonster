#include "Item/Item.h"

Item::Item() : Name(""), Price(0), Source(EItemSource::ShopPurchase) {}

Item::Item(const std::string& InName, int InPrice)
    : Name(InName), Price(InPrice), Source(EItemSource::ShopPurchase) {
}

void Item::SetSource(EItemSource InSource)
{
    Source = InSource;
}

EItemSource Item::GetSource() const
{
    return Source;
}

int Item::GetPrice() const
{
    return Price;
}
