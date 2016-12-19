#include "wdconfigdialog.h"
#include "ui_wdconfigdialog.h"

WDConfigDialog::WDConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WDConfigDialog)
{
    ui->setupUi(this);
    connect(ui->visible, SIGNAL(clicked(bool)), this, SIGNAL(visibleChange(bool)));
    connect(ui->hideEx, SIGNAL(clicked(bool)), this, SIGNAL(hideExChange(bool)));
    connect(ui->showError, SIGNAL(clicked(bool)), this, SIGNAL(showMSErrChange(bool)));
}

WDConfigDialog::~WDConfigDialog()
{
    delete ui;
}
