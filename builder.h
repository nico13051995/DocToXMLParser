#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include "models/item.h"
#include "models/paragraph.h"
#include "regexp.h"

/**
 * @brief The Builder interface for future extend of current functionality
 * create other builders
 */
class Builder : public QObject
{
    Q_OBJECT
public:
    Builder(QString name, QString header, QString footer);
    virtual QObject *build(QList<Item*> items, QList<Paragraph> paragraphs) = 0;

signals:

public slots:
protected:
    QString name;

    QString header;
    QString footer;

    RegExpTool rxTool;

};

#endif // BUILDER_H
