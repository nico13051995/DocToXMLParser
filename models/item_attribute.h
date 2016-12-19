#ifndef ITEMATTRIBUTE_H
#define ITEMATTRIBUTE_H

#include <QObject>
#include <QVariant>
#include "jsonserializable.h"

class Item;

class ItemAttribute : public JsonSerializable
{
    Q_OBJECT
    QString name;
    int type;
    QString value;
    bool enable = true;
public:
    explicit ItemAttribute(Item *parent = 0);
    ItemAttribute(QJsonObject obj, Item *parent = 0);
    bool load(QJsonObject obj);
    bool save(QJsonObject obj);

    QString getValue() const;
    QString getValue(QStringList mach) const;
    QString getName() const;
    void setName(const QString &value);

    int getType() const;
    void setType(int value);

signals:

public slots:
};

#endif // ITEMATTRIBUTE_H
