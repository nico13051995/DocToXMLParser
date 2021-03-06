#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include "item_attribute.h"


/**
 * @brief The Item class
 * Main model for searching
 */
class Item : public JsonSerializable
{
    Q_OBJECT

    QString name;
    QString regexp;
    QString value;
    int type;
    bool enable; // if true item will be ignored and dont added to result file
    bool useParentGroups; // parent scope prepeand to child
    bool useParentScope; // use parent fided results
    bool isList; //if true then try find next similar
    bool compareFontProperties;
    QList<ItemAttribute*> atributes;
    QList<Item*> childrens;
    QList<Item*> nextHope;//for performe only next paragraph
    int nextHopeIndex = 0;

public:
    explicit Item(QObject *parent = 0);
    ~Item();
    Item(QJsonObject obj, QObject *parent = 0);
    bool load(QJsonObject obj);
    bool save(QJsonObject obj);

    QList<Item *> getNextHope() const;
    void setNextHope(const QList<Item *> &value);

    QList<Item *> getChildrens() const;
    void setChildrens(const QList<Item *> &value);

    QList<ItemAttribute *> getAtributes() const;
    void setAtributes(const QList<ItemAttribute *> &value);

    QString getRegexp() const;
    void setRegexp(const QString &value);

    QString getName() const;
    void setName(const QString &value);

    int getType() const;
    void setType(int value);

    QString getValue() const;
    QString getValue(QStringList mach) const;

    bool getUseParentGroups() const;
    void setUseParentGroups(bool value);

    bool isEnable() const;
    void setEnable(bool value);

    bool getIsList() const;
    void setIsList(bool value);

    bool getUseParentScope() const;

    bool getCompareFontProperties() const;

    int getNextHopeIndex() const;

    void setNextHopeIndex(int value);

signals:

public slots:
};

#endif // ITEM_H
