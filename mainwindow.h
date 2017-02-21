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
    /**
     * Open file dialog and call performeFiles
    */
    void selectFilesWithDialog(bool selected);
    /**
     * Save result to XML file (FileDialog)
    */
    void exportTo();
    /**
     * Main calculation function
     * @param[in] filesList List of files path
     * @param[in] save If true then save result to xml file after calculation is done
    */
    void performeFiles(QStringList filesList, bool save = false);
    /**
     * Open folder dialog and call performeFiles
    */
    void selectFolder(bool selected);
    /**
    * Show dialog with parser configuaration
    */
    void showSelectParserConfigDialog();
    /**
    * Show dialog with Microsoft Word configuaration such as enable debug mode and so on.
    */
    void showMSWConfigDialog();
    /**
    * Generation of sample parser file with set path for save out file.
    * @return file from :/default.json
    */
    void generateMapSample();
private slots:
    /**
    * Required dialog which contain Qt Licence.
    */
    void aboutQt();
    /**
    * Show info dialog which contain general information about SW
    */
    void aboutParser();
    /**
    * Change text in status bar in async mode
    */
    void changeStatus(QString text, QColor color = Qt::black);
    /**
    * Change value of progress bar in status bar in async mode
    */
    void changeProgress(int value);

    /**
    * Functions for reconfig MS Word
    */
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
