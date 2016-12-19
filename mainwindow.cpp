#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":/license/xml-icon.ico"));
    selectConfigDialog = new SelectParserWindow(&supportedParserConfigs, this);
    debugConfig = new WDConfigDialog();
    showMSWordError = false;

    ui->setupUi(this);
    ui->progressBar->setValue(0);
    ui->status->setText("Done");

    builder = new XmlBuilder("XmlVNTU", "", "");

    connect(ui->actionOpen, SIGNAL(triggered(bool)), this, SLOT(selectFilesWithDialog(bool)));
    connect(ui->actionOpen_folder, SIGNAL(triggered(bool)), this, SLOT(selectFolder(bool)));
    connect(ui->actionExport_to, SIGNAL(triggered()), this, SLOT(exportTo()));
    connect(ui->actionSelect_parser_config, SIGNAL(triggered()), this, SLOT(showSelectParserConfigDialog()));
    connect(ui->actionDebug_WD, SIGNAL(triggered()), this, SLOT(showMSWConfigDialog()));
    connect(debugConfig, SIGNAL(visibleChange(bool)), this, SLOT(visibleMSChange(bool)));
    connect(debugConfig, SIGNAL(hideExChange(bool)), this, SLOT(hideExMSChange(bool)));
    connect(debugConfig, SIGNAL(showMSErrChange(bool)), this, SLOT(showMSErrChange(bool)));


    connect(ui->actionGenerate_map_sample, SIGNAL(triggered()), this, SLOT(generateMapSample()));
    connect(ui->actionAbout_Qt, SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(aboutParser()));

    supportedParserConfigs.append(new ParserConfig(DEFAULT_PATH, this));
    for(QString path : Settings::getInstance()->getSupportedMaps())
    {
        ParserConfig *temp = new ParserConfig(path, this);
        if(!temp->isValid())
        {
            Settings::getInstance()->removeMap(path);
            delete temp;
            continue;
        }
        supportedParserConfigs.append(temp);
    }


    wordApplication = new QAxObject("Word.Application", NULL);
    wordApplication->setProperty("Visible", QVariant(false));
    wordApplication->setProperty("OpenConflictDocument", QVariant(true));

    connect(wordApplication,
            SIGNAL(exception(int, const QString &, const QString &, const QString &)),
            this,
            SLOT(onAxWidgetException(int, const QString &, const QString &, const QString &)));
    documents = wordApplication->querySubObject("Documents");
    connect(documents,
            SIGNAL(exception(int, const QString &, const QString &, const QString &)),
            this,
            SLOT(onAxWidgetException(int, const QString &, const QString &, const QString &)));
}
void MainWindow::onAxWidgetException(int code, const QString & p1, const QString &p2, const QString &p3)
{
    qDebug() << "QAX_ERR:"<< showMSWordError << " " << code << p1 << p2 << p3;
    switch (code) {
    case 14:
        QMessageBox::warning(this, "Warning", "File can't be open for edition, check your permissions!!!\n You can have problem with numer list!!!");
        break;
    default:
        break;
    }

    if(showMSWordError)
        QMessageBox::warning(this, "ERROR", QString("Code%1\n\From:%2\nMsg(Locale MS):%3").arg(QString::number(code), p1, p2));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete selectConfigDialog;
    //documents->dynamicCall("Close (Boolean)", false);
    wordApplication->dynamicCall("Quit (void)");
    wordApplication->clear();
    delete documents;
    delete wordApplication;

}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::aboutParser()
{
    QFile license(":/license/license.txt");
    license.open(QFile::ReadOnly);
    QMessageBox::about(this, "About", license.readAll());
}

void MainWindow::changeStatus(QString text, QColor color)
{
    ui->status->setText(text);
    QPalette palette = ui->status->palette();
    palette.setColor(ui->status->foregroundRole(), color);
    ui->status->setPalette(palette);
    qApp->processEvents();
}

void MainWindow::changeProgress(int value)
{
    ui->progressBar->setValue(value);
    qApp->processEvents();
}

void MainWindow::visibleMSChange(bool value)
{
    qDebug() << "visibleMSChange:" << value;
    wordApplication->setProperty("Visible", QVariant(value));
}

void MainWindow::hideExMSChange(bool value)
{
    qDebug() << "hideExMSChange:" << value;
    wordApplication->setProperty("OpenConflictDocument", QVariant(value));
}
void MainWindow::showMSErrChange(bool value)
{
    this->showMSWordError = value;
    qDebug() << "showMSErrChange:" << this->showMSWordError;
}

void MainWindow::selectFilesWithDialog(bool selected)
{
    QStringList filesList = QFileDialog::getOpenFileNames(this);
    performeFiles(filesList);
}

void MainWindow::selectFolder(bool selected)
{
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        QString(),
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    QStringList filesList;
    QDir dirObj(dirPath);
    if(dirObj.exists())
    {
        QFileInfoList filesInfo = dirObj.entryInfoList(QDir::Files);
        for(QFileInfo info : filesInfo)
        {
            if(info.suffix() == "doc" || info.suffix() == "docx" || info.suffix() == "pdf")
                filesList.append(info.filePath());
        }
        performeFiles(filesList, true);
    }

}

void MainWindow::showSelectParserConfigDialog()
{
    selectConfigDialog->show();
}

void MainWindow::showMSWConfigDialog()
{
    debugConfig->show();
}

void MainWindow::generateMapSample()
{
    QString path = QFileDialog::getSaveFileName(this, "Create sample", "sample", "Json(*.json)");
    QFile file(path);
    QFile sample(DEFAULT_PATH);
    sample.open(QFile::ReadOnly);
    file.open(QFile::WriteOnly);
    if(file.isWritable())
    {
        file.write(sample.readAll());
        file.close();
    }
    changeStatus("Generation of sample success");
}

void MainWindow::exportTo()
{
    QString path = QFileDialog::getSaveFileName(this, "Save to xml", "", "XML(*.xml)");
    qDebug() << path;
    QFile file(path);
    file.open(QFile::WriteOnly);
    if(file.isWritable())
    {
        file.write(ui->textBrowser->toPlainText().toUtf8());
        file.close();
        changeStatus("Export success", Qt::darkGreen);
    }
    changeStatus("Export faild", Qt::darkRed);
}

void MainWindow::performeFiles(QStringList filesList, bool save)
{

    ui->progressBar->setValue(0);
    int counter=1;
    for(QString fileName : filesList)
    {
        double filePart = (double)1/filesList.size();
        changeStatus("Load file:" + fileName, Qt::darkBlue);
        QAxObject *document = documents->querySubObject("Open(QString, QVariant, QVariant)", fileName.replace('/', '\\' ), false, false);
        /* QAxObject *words = document->querySubObject("Words");
        QAxObject *sentences = document->querySubObject("Sentences");*/
        if(document == NULL)
        {
            QMessageBox::information(this,"Info", "File is not existed or name is not supported. Try rename the file :)");
            return;
        }
        QAxObject *paragraphs = document->querySubObject("Paragraphs");
        QAxObject *headWords = document->querySubObject("Sections")->querySubObject("Item(QVariant)", 1)->querySubObject("Headers")->querySubObject("Item(QVariant)", 1)
                ->querySubObject("Range")->querySubObject("Words");

        /*
        if(sentences != NULL)
        {
            QString textResult;
            int countWord = sentences->dynamicCall("Count()").toInt();
            for (int a = 1; a <= countWord; a++){
                textResult.append(sentences->querySubObject("Item(QVariant)", a)->dynamicCall("Text()").toString());
                qDebug() << textResult;
            }

        }*/

        QJsonObject result;

        QAxObject *activeDoc=wordApplication->querySubObject("ActiveDocument");
        connect(activeDoc,
                SIGNAL(exception(int, const QString &, const QString &, const QString &)),
                this,
                SLOT(onAxWidgetException(int, const QString &, const QString &, const QString &)));
        // QAxObject *range=activeDoc->querySubObject("Range");
        QVariant v = activeDoc->dynamicCall("ConvertNumbersToText()");
        // range->querySubObject("ListFormat()")->dynamicCall("ConvertNumbersToText()");

        // lists->querySubObject("Item(QVariant)", a)->dynamicCall("ConvertNumbersToText()").toString();



        int countWord = headWords->dynamicCall("Count()").toInt();
        QString textResult;
        for (int a = 1; a <= countWord; a++){
            textResult.append(headWords->querySubObject("Item(QVariant)", a)->dynamicCall("Text()").toString());
        }
        result["name"] = QJsonValue(textResult);
        /*RegExpTool regExp;
        QStringList list = regExp.globalMatch(textResult, "(\\w+.+?) *, *(\\s?.+\\s?)+ *, *(\\d+) *, № (\\d+)");
        qDebug() << textResult;
        qDebug() << list;
*/
        QList<QString> listTets;
        listTets.append(textResult);

        if(paragraphs != NULL)
        {
            int countParagraphs = paragraphs->dynamicCall("Count()").toInt();
            for (int a = 1; a <= countParagraphs; a++){
                QAxObject *range = paragraphs->querySubObject("Item(QVariant)", a)->querySubObject("Range");
                /* QAxObject *words = range->querySubObject("Words");
                int countWord = words->dynamicCall("Count()").toInt();
                QString textResult;
                for (int a = 1; a <= countWord; a++){
                    textResult.append(words->querySubObject("Item(QVariant)", a)->dynamicCall("Text()").toString());
                }
                listTets.append(textResult);*/
                QString value = range->dynamicCall("Text()").toString();
                if(value != "\r")
                    listTets.append(value);
                //qDebug() << textResult;

                changeProgress(filePart*counter*100 + (((double)a/countParagraphs)*filePart*100));

            }

        }
        if(builder != NULL)
        {
            delete builder;
        }
        builder = new XmlBuilder(selectConfigDialog->getCurrentConfig()->getName(), selectConfigDialog->getCurrentConfig()->getHeader(), selectConfigDialog->getCurrentConfig()->getFooter());
        changeStatus("Procces file", Qt::darkBlue);
        QString res = *(QString*)builder->build(selectConfigDialog->getCurrentConfig()->getCurrentTemplate(), listTets);
        ui->textBrowser->setPlainText(res);
        // qDebug() << res;

        if(save)
        {
            QFileInfo info(fileName);
            QFile file(info.absolutePath() + "/" + info.baseName() + ".xml");
            file.open(QFile::WriteOnly);
            if(file.isWritable())
            {
                file.write(res.toUtf8());
                file.close();
            }
            //qDebug() << info.absolutePath() + info.baseName() + ".xml";
        }
        document->dynamicCall("Close (Boolean)", false);
        delete headWords;
        delete paragraphs;
        delete document;
        counter++;
    }
    changeStatus("Success", Qt::darkGreen);
    // ui->progressBar->setValue(0);
}
