#ifndef WDCONFIGDIALOG_H
#define WDCONFIGDIALOG_H

#include <QDialog>
#include <QtCore>
#include "models/settingscontainer.h"

namespace Ui {
class WDConfigDialog;
}

class WDConfigDialog : public QDialog
{
    Q_OBJECT
public:
    WDConfigDialog(QWidget *parent = 0);
    ~WDConfigDialog();
signals:
    void visibleChange(bool value);
    void hideExChange(bool value);
    void showMSErrChange(bool value);
private:
    Ui::WDConfigDialog *ui;
};

#endif // WDCONFIGDIALOG_H
