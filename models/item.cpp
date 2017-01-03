#include "item.h"
#include <QDebug>

QList<Item *> Item::getNextHope() const
{
    return nextHope;
}

void Item::setNextHope(const QList<Item *> &value)
{
    nextHope = value;
}

QList<Item *> Item::getChildrens() const
{
    return childrens;
}

void Item::setChildrens(const QList<Item *> &value)
{
    childrens = value;
}

QList<ItemAttribute *> Item::getAtributes() const
{
    return atributes;
}

void Item::setAtributes(const QList<ItemAttribute *> &value)
{
    atributes = value;
}

QString Item::getRegexp() const
{
    return regexp;
}

void Item::setRegexp(const QString &value)
{
    regexp = value;
}

QString Item::getName() const
{
    return name;
}

void Item::setName(const QString &value)
{
    name = value;
}

int Item::getType() const
{
    return type;
}

void Item::setType(int value)
{
    type = value;
}

QString Item::getValue() const
{
    return value;
}

QString Item::getValue(QStringList mach) const
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

bool Item::getUseParentGroups() const
{
    return useParentGroups;
}

void Item::setUseParentGroups(bool value)
{
    useParentGroups = value;
}

bool Item::isEnable() const
{
    return enable;
}

void Item::setEnable(bool value)
{
    enable = value;
}

bool Item::getIsList() const
{
    return isList;
}

void Item::setIsList(bool value)
{
    isList = value;
}

bool Item::getUseParentScope() const
{
    return useParentScope;
}

bool Item::getCompareFontProperties() const
{
    return compareFontProperties;
}

int Item::getNextHopeIndex() const
{
    return nextHopeIndex;
}

void Item::setNextHopeIndex(int value)
{
    nextHopeIndex = value;
}

Item::Item(QObject *parent) : JsonSerializable(parent)
{
    enable = true;
}
//carbadge remove
Item::~Item()
{
    for(Item* value : childrens)
    {
        delete value;
    }
    for(Item* value : nextHope)
    {
        delete value;
    }
    for(ItemAttribute* value : atributes)
    {
        delete value;
    }
}

Item::Item(QJsonObject obj, QObject *parent): JsonSerializable(parent)
{
    load(obj);
}

bool Item::load(QJsonObject obj)
{
    enable = true;
    compareFontProperties = false;
    isList = false;
    useParentGroups = false;
    useParentScope = false;
    name = obj["name"].toString();
    regexp = obj["regexp"].toString();
    value = obj["value"].toString();
    type = obj["type"].toInt();
    if(obj.contains("useParentGroups"))
        useParentGroups = obj["useParentGroups"].toBool();
    if(obj.contains("useParentScope"))
        useParentScope = obj["useParentScope"].toBool();
    if(obj.contains("enable"))
        enable = obj["enable"].toBool();
    if(obj.contains("compareFontProperties"))
        compareFontProperties = obj["compareFontProperties"].toBool();

    if(obj.contains("list"))
    {
        isList = obj["list"].toBool();
        qDebug() << "AAAAAAAA" << isList;
    }

    for(QJsonValue value : obj["childrens"].toArray())
    {
        Item *child = new Item(value.toObject(), this);
        childrens.append(child);
    }
    for(QJsonValue value : obj["nextHope"].toArray())
    {
        nextHope.append(new Item(value.toObject()));
    }
    for(QJsonValue value : obj["atributes"].toArray())
    {
        atributes.append(new ItemAttribute(value.toObject(), this));
    }
}

bool Item::save(QJsonObject obj)
{

}
