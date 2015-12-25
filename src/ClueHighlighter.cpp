#include "ClueHighlighter.h"

#include <QRegExp>
#include <QString>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

ClueHighlighter::ClueHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
}

void ClueHighlighter::highlightBlock(const QString& text)
{
    QTextCharFormat myClassFormat;
    myClassFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    QString pattern = "\\b[A-Za-z]+\\b";

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
     }
}
