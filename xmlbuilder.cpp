#include "xmlbuilder.h"
#include <QDebug>

QXmlStreamWriter *XmlBuilder::getXml()
{
    return xml;
}

XmlBuilder::XmlBuilder(QString name, QString header, QString footer) : Builder(name, header, footer)
{
    result = new QString();
    xml = new QXmlStreamWriter(result);
    xml->setAutoFormatting(true);
}

QObject* XmlBuilder::build(QList<Item *> items, QList<QString> paragraphs)
{
    result->clear();
    *result += header;
    build(QStringList(), items, paragraphs);
    *result += footer;
    return (QObject*)result;
}

QString XmlBuilder::getResultAsString()
{
    return *result;
}

QObject *XmlBuilder::build(QStringList parentMatch, QList<Item *> items, QList<QString> paragraphs)
{
    for(Item* item : items)
    {
        int infoListIndicator = false;
        for(int pIndex = 0; pIndex < paragraphs.size(); pIndex++)
        {
            QStringList findList = rxTool.globalMatch(paragraphs[pIndex], item->getRegexp());
            if(item->getUseParentGroups())
                findList = parentMatch + findList;
            if(findList.size() > 0)
            {
                infoListIndicator = true;
                if(item->isEnable())
                {
                    xml->writeStartElement(item->getName());
                    for(ItemAttribute *atribute : item->getAtributes())
                    {
                        xml->writeAttribute(atribute->getName(), atribute->getValue(findList).trimmed().toHtmlEscaped());
                    }
                    xml->writeCharacters(item->getValue(findList).trimmed().toHtmlEscaped());
                    QList<QString> listParagraphs;
                    listParagraphs.append(paragraphs.at(pIndex));
                    for(int i = 0 ; i < item->getChildrens().size(); i++){
                        QList<Item*> listItems;
                        listItems.append(item->getChildrens().at(i));
                        if(item->getChildrens().at(i)->getUseParentScope())
                            build(findList, listItems, listParagraphs);
                        else
                            build(findList, listItems, paragraphs);
                    }
                    xml->writeEndElement();
                }
                for(int i = 0 ; i < item->getNextHope().size(); i++){
                    QList<Item*> listItems;
                    listItems.append(item->getNextHope().at(i));

                    QList<QString> listParagraphs;

                    qDebug() << item->getNextHope().at(i)->getIsList();
                    if(item->getNextHope().at(i)->getIsList())
                        build(findList, listItems, paragraphs.mid(i + pIndex + 1));
                    else
                    {
                        if(item->getNextHope().at(i)->getUseParentScope())
                            listParagraphs.append(paragraphs.at(i + pIndex));
                        else
                            listParagraphs.append(paragraphs.at(i + pIndex + 1));
                        build(findList, listItems, listParagraphs);
                    }

                }
                if(item->getIsList() == false)
                    break;
            }
            else{
                if(infoListIndicator && item->getIsList() == true)
                    break;
            }
        }
    }
}
