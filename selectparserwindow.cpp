#include "selectparserwindow.h"
#include "ui_selectparserwindow.h"

SelectParserWindow::SelectParserWindow(QList<ParserConfig *> *list, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectParserWindow)
{
    currentConfig = NULL;
    ui->setupUi(this);
    this->list = list;
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)));
    connect(ui->importSelectFile, SIGNAL(pressed()), this, SLOT(showFileDialog()));
    connect(ui->importBtn, SIGNAL(pressed()), this, SLOT(import()));
    connect(ui->removeBtn, SIGNAL(pressed()), this, SLOT(remove()));
    connect(ui->editBtn, SIGNAL(pressed()), this, SLOT(edit()));

//    connect(ui->import_info, SIGNAL())


}

SelectParserWindow::~SelectParserWindow()
{
    delete ui;
}

void SelectParserWindow::showEvent(QShowEvent *e)
{
    QDialog::showEvent(e);
    ui->import_info->setText("Wait");
    QPalette palette = ui->import_info->palette();
    palette.setColor(ui->import_info->foregroundRole(), Qt::blue);
    ui->import_info->setPalette(palette);

    update();
}
void SelectParserWindow::update(){
     ui->comboBox->clear();
    for(ParserConfig *config : *list)
    {
        ui->comboBox->addItem(config->getName(), config->getPath());
        if(currentConfig == config)
            ui->comboBox->setCurrentText(config->getName());
    }
}

ParserConfig *SelectParserWindow::getCurrentConfig()
{
    if(currentConfig == NULL)
    {
        currentConfig = list->first();
    }
    return currentConfig;
}

void SelectParserWindow::currentIndexChanged(int index)
{
    //qDebug() << "BBBB" << list->at(index)->getPath().trimmed();
    if(index == -1 || list->at(index)->getPath().trimmed()[0] == ':')
    {
        ui->editBtn->hide();
        ui->removeBtn->hide();
    }
    else
    {
        ui->editBtn->show();
        ui->removeBtn->show();
    }
    if(index > 0 && list->size() > index)
        currentConfig = list->at(index);
}

void SelectParserWindow::showFileDialog()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open map", "", "Json(*.json)");
    ui->lineEdit->setText(filePath);
    ParserConfig test(filePath);
    QPalette palette = ui->import_info->palette();
    bool isValid = test.isValid();
    ui->importBtn->setEnabled(isValid);
    if(isValid)
    {
        palette.setColor(ui->import_info->foregroundRole(), Qt::darkGreen);
        ui->import_info->setText("is valid");
    }
    else{
        palette.setColor(ui->import_info->foregroundRole(), Qt::red);
        ui->import_info->setText("is invalid");
    }
    ui->import_info->setPalette(palette);
}

void SelectParserWindow::import()
{
    ParserConfig *config = new ParserConfig(ui->lineEdit->text());
    list->append(config);
    ui->comboBox->addItem(config->getName(), config->getPath());
    Settings::getInstance()->addNewMap(config->getPath());
    ui->import_info->setText("sucsess");
}

void SelectParserWindow::edit(){
    QDesktopServices::openUrl(ui->comboBox->currentData().toString());
}

void SelectParserWindow::remove(){
    Settings::getInstance()->removeMap(ui->comboBox->currentData().toString());
    list->removeAt(ui->comboBox->currentIndex());
    ui->comboBox->removeItem(ui->comboBox->currentIndex());
}
