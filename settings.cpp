#include "settings.h"

Settings * Settings::instance;

Settings::Settings()
{
    //if(QFile("settings.conf").exists())
    settings = new QSettings("configure.ini", QSettings::IniFormat);

}

Settings::~Settings()
{
    delete settings;
}

Settings *Settings::getInstance()
{
    if(Settings::instance == NULL)
        Settings::instance = new Settings();
    return Settings::instance;
}
QStringList Settings::getSupportedMaps()
{
    return settings->value("supportedMaps/items").toStringList();
}

bool Settings::addNewMap(QString path)
{
    QStringList paths = settings->value("supportedMaps/items").toStringList();
    paths.append(path);
    settings->setValue("supportedMaps/items", QVariant::fromValue(paths));
    settings->sync();
    if(settings->status() != QSettings::NoError)
        QMessageBox::warning(NULL, "ERR", "Problem with settings");
}

bool Settings::removeMap(QString path)
{
    QStringList paths = settings->value("supportedMaps/items").toStringList();
    paths.removeAll(path);
    settings->setValue("supportedMaps/items", QVariant::fromValue(paths));
    settings->sync();
    if(settings->status() != QSettings::NoError)
        QMessageBox::warning(NULL, "ERR", "Problem with settings");
}
