#include "paragraph.h"

QFont Paragraph::getFont() const
{
    return font;
}

void Paragraph::setFont(const QFont &value)
{
    font = value;
}

QString Paragraph::getText() const
{
    return text;
}

void Paragraph::setText(const QString &value)
{
    text = value;
}

Paragraph::Paragraph(QString text, QFont font) : text(text), font(font)
{

}
