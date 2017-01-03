#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <QString>
#include <QFont>

class Paragraph
{

    QString text;
    QFont font;
public:
    Paragraph( QString text, QFont font);

    QFont getFont() const;
    void setFont(const QFont &value);
    QString getText() const;
    void setText(const QString &value);
};

#endif // PARAGRAPH_H
