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

QObject* XmlBuilder::build(QList<Item *> items, QList<Paragraph> paragraphs)
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

QObject *XmlBuilder::build(QStringList parentMatch, QList<Item *> items, QList<Paragraph> paragraphs)
{
    for(Item* item : items)
    {
        int infoListIndicator = false;
        QFont firstFont;//for watch font changes
        for(int pIndex = 0; pIndex < paragraphs.size(); pIndex++)
        {
            QStringList findList = rxTool.globalMatch(paragraphs[pIndex].getText(), item->getRegexp());//finded results
            if(item->getUseParentGroups())
                findList = parentMatch + findList;
            item->setNextHopeIndex(pIndex);
            if(findList.size() > 0)
            {
                if(infoListIndicator == false)
                {
                    firstFont = paragraphs[pIndex].getFont();
                }
                infoListIndicator = true;
                if(item->isEnable())
                {
                    xml->writeStartElement(item->getName());
                    for(ItemAttribute *atribute : item->getAtributes())
                    {
                        xml->writeAttribute(atribute->getName(), atribute->getValue(findList).trimmed().toHtmlEscaped());//write atributes
                    }

                    QString text = item->getValue(findList).trimmed().toHtmlEscaped();
                    if(item->getCompareFontProperties())//compare font if need
                    {
                        while(pIndex + 1 < paragraphs.size() && firstFont == paragraphs[pIndex + 1].getFont())
                        {
                            if(rxTool.globalMatch(paragraphs[pIndex + 1].getText(), item->getRegexp()).size() > 0)
                                break;
                            pIndex++;
                            text += paragraphs[pIndex].getText().trimmed().toHtmlEscaped();
                        }
                          item->setNextHopeIndex(pIndex);
                    }
                    xml->writeCharacters(text);//write content after atributes
                    QList<Paragraph> listParagraphs;
                    listParagraphs.append(paragraphs.at(pIndex));
                    for(int i = 0 ; i < item->getChildrens().size(); i++){
                        QList<Item*> listItems;
                        listItems.append(item->getChildrens().at(i));
                        if(item->getChildrens().at(i)->getUseParentScope())
                            build(findList, listItems, listParagraphs);
                        else
                            build(findList, listItems, paragraphs);
                    }
                    xml->writeEndElement();//write footer
                }
                for(int i = 0 ; i < item->getNextHope().size(); i++){//check next home items
                    QList<Item*> listItems;
                    listItems.append(item->getNextHope().at(i));

                    QList<Paragraph> listParagraphs;
                    int previusPindex = 0;
                    if(i > 0)
                        previusPindex = item->getNextHope()[i - 1]->getNextHopeIndex();

                    qDebug() << item->getName() << "::" << item->getNextHope().at(i)->getCompareFontProperties();
                    if(item->getNextHope().at(i)->getIsList() || item->getNextHope().at(i)->getCompareFontProperties())
                        build(findList, listItems, paragraphs.mid(i + previusPindex + pIndex + 1));
                    else
                    {
                        if(item->getNextHope().at(i)->getUseParentScope())
                            listParagraphs.append(paragraphs.at(i + previusPindex + pIndex));
                        else
                            listParagraphs.append(paragraphs.at(i + previusPindex + pIndex + 1));
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
