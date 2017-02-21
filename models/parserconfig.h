#ifndef PARSERCONFIG_H
#define PARSERCONFIG_H

#include <QObject>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QAxObject>
#include <QDebug>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "item.h"

/**
 * @brief The ParserConfig class
 */
class ParserConfig : public QObject
{
    Q_OBJECT

    QString path;
    QString name;

    QString header;
    QString footer;

    /**
     * @brief currentTemplate
     * list of item readed from config files
     */
    QList<Item *> currentTemplate;
public:
    ParserConfig(QString path, QObject *parent = 0);
    ~ParserConfig();
    bool isValid();

    QList<Item *> getCurrentTemplate() const;

    QString getName() const;

    QString getPath() const;

    QString getFooter() const;

    QString getHeader() const;

signals:

public slots:
    /**
     * @brief readJson
     * @param path to json file
     * @return if true then reading is successfull else all so bad :(
     */
    bool readJson(QString path);
};

#endif // PARSERCONFIG_H
