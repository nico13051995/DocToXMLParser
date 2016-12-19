#include "builder.h"

Builder::Builder(QString name, QString header, QString footer) : QObject(NULL)
{
    this->name = name;
    this->header = header;
    this->footer = footer;
}
