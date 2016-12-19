#include "item_attribute.h"
#include "item.h"

QString ItemAttribute::getName() const
{
    return name;
}

void ItemAttribute::setName(const QString &value)
{
    name = value;
}

int ItemAttribute::getType() const
{
    return type;
}

void ItemAttribute::setType(int value)
{
    type = value;
}

ItemAttribute::ItemAttribute(Item *parent) : JsonSerializable(parent)
{

}

ItemAttribute::ItemAttribute(QJsonObject obj, Item *parent) : JsonSerializable(parent)
{
    load(obj);
}

bool ItemAttribute::load(QJsonObject obj)
{
    enable = true;
    name = obj["name"].toString();
    type = obj["type"].toInt();
    value = obj["value"].toString();
    if(obj.contains("enable"))
        enable = obj["enable"].toBool();
    return true;
}
bool ItemAttribute::save(QJsonObject obj)
{
    obj["name"] = name;
    obj["type"] = type;
    obj["value"] = value;
    return true;
}

QString ItemAttribute::getValue() const
{
    return value;
}

QString ItemAttribute::getValue(QStringList mach) const
{
    switch (type) {
    case 0:
        return mach[value.toInt()];
        break;
    case 1:
        return value;
    default:
        break;
    }
}
