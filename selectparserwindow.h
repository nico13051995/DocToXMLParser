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
/**
 * @brief The SelectParserWindow class
 */
class SelectParserWindow : public QDialog
{
    Q_OBJECT

    /**
     * @brief list of supported configurations
     */
    QList<ParserConfig*> *list;
    /**
     * @brief currentConfig - object with current loaded configurations
     */
    ParserConfig *currentConfig;
public:
    /**
     * @brief SelectParserWindow
     * @param list - list for init started configurations
     * @param parent - parent windows pointer
     */
    SelectParserWindow(QList<ParserConfig *> *list, QWidget *parent = 0);
    ~SelectParserWindow();

    /**
     * @brief showEvent - prefunction for update UI
     * @param e
     */
    void showEvent(QShowEvent *e);
    ParserConfig *getCurrentConfig();
public slots:

private slots:
    void currentIndexChanged(int index);
    void showFileDialog();
    /**
     * @brief import
     */
    void import();
    /**
     * @brief remove
     */
    void remove();
    /**
     * @brief edit
     */
    void edit();
private:

    Ui::SelectParserWindow *ui;
    /**
     * @brief update UI with list of supported configurations
     */
    void update();
};

#endif // SELECTPARSERWINDOW_H
