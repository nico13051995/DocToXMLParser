#ifndef JSONSERIALIZABLE_H
#define JSONSERIALIZABLE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

class JsonSerializable : public QObject
{
    Q_OBJECT
public:
    explicit JsonSerializable(QObject *parent = 0);
    virtual bool load(QJsonObject obj) = 0;
    virtual bool save(QJsonObject obj) = 0;
signals:

public slots:
};

#endif // JSONSERIALIZABLE_H
