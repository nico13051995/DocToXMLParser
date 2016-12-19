#ifndef SELECTPARSERWINDOW_H
#define SELECTPARSERWINDOW_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>
#include "models/parserconfig.h"
#include "settings.h"

namespace Ui {
class SelectParserWindow;
}

class SelectParserWindow : public QDialog
{
    Q_OBJECT

    QList<ParserConfig*> *list;
    ParserConfig *currentConfig;
public:
    SelectParserWindow(QList<ParserConfig *> *list, QWidget *parent = 0);
    ~SelectParserWindow();

    void showEvent(QShowEvent *e);
    ParserConfig *getCurrentConfig();
public slots:

private slots:
    void currentIndexChanged(int index);
    void showFileDialog();
    void import();
    void remove();
    void edit();
private:

    Ui::SelectParserWindow *ui;
    void update();
};

#endif // SELECTPARSERWINDOW_H
