#include "parserconfig.h"

QList<Item *> ParserConfig::getCurrentTemplate() const
{
    return currentTemplate;
}

QString ParserConfig::getName() const
{
    return name;
}

QString ParserConfig::getPath() const
{
    return path;
}

QString ParserConfig::getFooter() const
{
    return footer;
}

QString ParserConfig::getHeader() const
{
    return header;
}

ParserConfig::ParserConfig(QString path, QObject *parent) : QObject(parent)
{
    this->path = path;
    readJson(path);
}

ParserConfig::~ParserConfig()
{
    for(Item* value : currentTemplate)
    {
        delete value;
    }
}

bool ParserConfig::isValid()
{
    return !currentTemplate.isEmpty();
}

bool ParserConfig::readJson(QString path)
{
    QList<Item*> _currentTemplate;
    QString val;
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!file.exists())
        return false;

    val = file.readAll();
    file.close();
    name = QFileInfo(path).baseName();

    QJsonArray items;
    QJsonDocument document = QJsonDocument::fromJson(val.toUtf8());
    if(document.isObject())
    {
        QJsonObject root = document.object();
        if(root.contains("name"))
        {
            name = root["name"].toString();
        }
        if(root.contains("header"))
        {
            header = root["header"].toString();
        }
        if(root.contains("footer"))
        {
            footer = root["footer"].toString();
        }
        if(!root.contains("items") || !root["items"].isArray())
            return false;
        items = root["items"].toArray();
    }
    if(document.isArray())
    {
        items = document.array();
    }

    // qWarning() << document.toJson();
    for(QJsonValue value : items)
    {
        Item *item = new Item(value.toObject());
        /* for(Item *child : item->getChildrens())
            _currentTemplate.append(child);*/
        _currentTemplate.append(item);
    }
    currentTemplate = _currentTemplate;
    return true;
    //   qDebug() << currentTemplate;
    /*QJsonValue value = sett2.value(QString("appName"));
      qWarning() << value;
      QJsonObject item = value.toObject();
      qWarning() << tr("QJsonObject of description: ") << item;

      qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
      QJsonValue subobj = item["description"];
      qWarning() << subobj.toString();

      qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
      QJsonArray test = item["imp"].toArray();
      qWarning() << test[1].toString();*/
}
