#ifndef SETTINGSCONTAINER_H
#define SETTINGSCONTAINER_H

#include <QObject>

class SettingsContainer : public QObject
{
    Q_OBJECT
public:
    explicit SettingsContainer(QObject *parent = 0);

signals:

public slots:
};

#endif // SETTINGSCONTAINER_H