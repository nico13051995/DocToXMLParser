#ifndef REGEXP_H
#define REGEXP_H

#include <QObject>

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>
#include <QDebug>


/**
 * @brief The RegExpTool class
 * Specific class tool for fast parsing document
 *
 */
class RegExpTool : public QObject
{
    Q_OBJECT
    QString pattern = "";
    QString text = "";
    QRegularExpression rx;


    QRegularExpression::MatchType matchType = QRegularExpression::MatchType::NormalMatch;
    QRegularExpression::PatternOptions patternOptions = QRegularExpression::NoPatternOption;
    QRegularExpression::MatchOptions matchOptions = QRegularExpression::NoMatchOption;
public:
    explicit RegExpTool(QObject *parent = 0);
    QStringList globalMatch(QString text, QString pattern = QString());

    bool setPatter(QString pattern);
    const QStringList getGroupsNames(QString pattern = QString());

signals:

public slots:
};

#endif // REGEXP_H
