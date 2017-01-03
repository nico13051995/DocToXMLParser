#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QAxObject>
#include <QDebug>
#include <QSettings>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "selectparserwindow.h"
#include "wdconfigdialog.h"
#include "models/parserconfig.h"
#include "models/paragraph.h"
#include "models/item.h"
#include "xmlbuilder.h"

#define DEFAULT_PATH ":/default.json"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QList<ParserConfig*> supportedParserConfigs;
    Builder *builder;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectFilesWithDialog(bool selected);
    void exportTo();
    void performeFiles(QStringList filesList, bool save = false);
    void selectFolder(bool selected);
    void showSelectParserConfigDialog();
    void showMSWConfigDialog();
    void generateMapSample();
private slots:
    void aboutQt();
    void aboutParser();

    void changeStatus(QString text, QColor color = Qt::black);
    void changeProgress(int value);

    void visibleMSChange(bool value);
    void hideExMSChange(bool value);
    void showMSErrChange(bool value);

    void onAxWidgetException(int code, const QString &p1, const QString &p2, const QString &p3);

private:
    Ui::MainWindow *ui;
    SelectParserWindow *selectConfigDialog;
    WDConfigDialog *debugConfig;
    QAxObject *wordApplication;
    QAxObject *documents;

    bool showMSWordError;

};

#endif // MAINWINDOW_H
