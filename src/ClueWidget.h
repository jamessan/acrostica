#ifndef ACROSTICA_CLUEWIDGET_H
#define ACROSTICA_CLUEWIDGET_H

#include <QGroupBox>

class ClueHighlighter;
class QLabel;
class QPlainTextEdit;
class QString;
class QWidget;

class ClueWidget : public QGroupBox
{
  Q_OBJECT

public:
  ClueWidget(const QString& title, QWidget *parent = 0);
  QString toPlainText() const;

signals:
  void textChanged();

private slots:
  void proxyTextChanged();

private:
  QPlainTextEdit *clue, *answer;
  ClueHighlighter *highlighter;
};

#endif
