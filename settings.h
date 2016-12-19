#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

class Settings
{
    QSettings *settings;

    Settings();
    ~Settings();

    static Settings *instance;
public:
    static Settings *getInstance();

    bool addNewMap(QString path);

public slots:
    QStringList getSupportedMaps();
    bool removeMap(QString path);
};

#endif // SETTINGS_H
