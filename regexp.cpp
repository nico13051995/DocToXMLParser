#include "regexp.h"


RegExpTool::RegExpTool(QObject *parent) : QObject(parent)
{
    QString escaped = pattern;
    escaped.replace(QLatin1String("\\"), QLatin1String("\\\\"));
    escaped.replace(QLatin1String("\""), QLatin1String("\\\""));
    escaped.prepend(QLatin1Char('"'));
    escaped.append(QLatin1Char('"'));

    rx.setPattern(pattern);
    rx.setPatternOptions(patternOptions);
}

QStringList RegExpTool::globalMatch(QString text, QString pattern)
{
    QStringList list;
    QString oldPattern;
    if(!pattern.isEmpty())
    {
        oldPattern = rx.pattern();
        QString escaped = pattern;
        escaped.replace(QLatin1String("\\"), QLatin1String("\\\\"));
        escaped.replace(QLatin1String("\""), QLatin1String("\\\""));
        escaped.prepend(QLatin1Char('"'));
        escaped.append(QLatin1Char('"'));
        rx.setPattern(pattern);
    }
    if (rx.isValid()) {
        const int capturingGroupsCount = rx.captureCount() + 1;

        QRegularExpressionMatchIterator iterator = rx.globalMatch(text.simplified(), 0, matchType, matchOptions);
        int i = 0;

        while (iterator.hasNext()) {
            QRegularExpressionMatch match = iterator.next();
            for (int captureGroupIndex = 0; captureGroupIndex < capturingGroupsCount; ++captureGroupIndex) {
                qDebug() << "index:" << QString::number(captureGroupIndex);
                qDebug() << "value:" << match.captured(captureGroupIndex) << "\n";
                list.append(match.captured(captureGroupIndex));
            }
            ++i;
        }
    }
    if(!oldPattern.isEmpty())
    {
        rx.setPattern(oldPattern);
    }
    return list;
}

bool RegExpTool::setPatter(QString pattern)
{
    QString oldPattern = rx.pattern();
    rx.setPattern(pattern);
    if(rx.isValid())
        this->pattern = pattern;
    else
        rx.setPattern(oldPattern);
    return rx.isValid();
}

const QStringList RegExpTool::getGroupsNames(QString pattern)
{
    QString oldPattern;
    if(!pattern.isEmpty())
    {
        oldPattern = rx.pattern();
        rx.setPattern(pattern);
    }
    if (rx.isValid()) {
        const QStringList namedCaptureGroups = rx.namedCaptureGroups();
        for (int i = 0; i < namedCaptureGroups.size(); ++i) {
            const QString currentNamedCaptureGroup = namedCaptureGroups.at(i);
            qDebug() << "index:" <<  QString::number(i);
            qDebug() << "name:" << (currentNamedCaptureGroup.isNull() ? tr("<no name>") : currentNamedCaptureGroup);
        }
    }
    if(!oldPattern.isEmpty())
    {
        rx.setPattern(oldPattern);
    }

}
