#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include "models/item.h"
#include "regexp.h"

class Builder : public QObject
{
    Q_OBJECT
public:
    Builder(QString name, QString header, QString footer);
    virtual QObject *build(QList<Item*> items, QList<QString> paragraphs) = 0;

signals:

public slots:
protected:
    QString name;

    QString header;
    QString footer;

    RegExpTool rxTool;

};

#endif // BUILDER_H
