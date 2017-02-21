#ifndef XMLBUILDER_H
#define XMLBUILDER_H

#include <QObject>
#include <QXmlStreamWriter>
#include "builder.h"

/**
 * @brief The XmlBuilder class
 * implementation of Builder for XML generator
 */
class XmlBuilder : public Builder
{
    Q_OBJECT
    QXmlStreamWriter *xml;
    QString *result;
public:
    XmlBuilder(QString name, QString header, QString footer);
    QObject *build(QList<Item*> items, QList<Paragraph> paragraphs);
    /**
     * @brief getResultAsString - get XML string from QXmlStreamWriter
     * @return string with result XML
     */
    QString getResultAsString();

    QXmlStreamWriter *getXml();
private:
    /**
     * @brief build - main function for parse
     * @param parentMatch - finded result of previus iteration
     * @param items - item which need search
     * @param paragraphs - paragraphs for search
     * @return
     */
    QObject *build(QStringList parentMatch, QList<Item *> items, QList<Paragraph> paragraphs);

signals:

public slots:
};

#endif // XMLBUILDER_H
