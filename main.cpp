#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("My Company");
    a.setOrganizationDomain("mycompany.com");
    a.setApplicationName("My Application");
    QCoreApplication::setOrganizationName("org");
        QCoreApplication::setApplicationName("app");
    MainWindow w;
    w.show();

    return a.exec();
}
