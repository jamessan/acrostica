#ifndef ACROSTICA_CLUEHIGHLIGHTER_H
#define ACROSTICA_CLUEHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QString;
class QTextDocument;

class ClueHighlighter : public QSyntaxHighlighter
{
public:
    ClueHighlighter(QTextDocument* parent);
    void highlightBlock(const QString& text);
};

#endif
