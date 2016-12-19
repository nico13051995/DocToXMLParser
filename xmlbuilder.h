#ifndef XMLBUILDER_H
#define XMLBUILDER_H

#include <QObject>
#include <QXmlStreamWriter>
#include "builder.h"

class XmlBuilder : public Builder
{
    Q_OBJECT
    QXmlStreamWriter *xml;
    QString *result;
public:
    XmlBuilder(QString name, QString header, QString footer);
    QObject *build(QList<Item*> items, QList<QString> paragraphs);
    QString getResultAsString();

    QXmlStreamWriter *getXml();
private:
    QObject *build(QStringList parentMatch, QList<Item *> items, QList<QString> paragraphs);

signals:

public slots:
};

#endif // XMLBUILDER_H
