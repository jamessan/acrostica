#ifndef ACROSTICA_CLUEWIDGET_H
#define ACROSTICA_CLUEWIDGET_H

#include <QGroupBox>

class ClueHighlighter;
class QLabel;
class QLineEdit;
class QString;
class QWidget;

class ClueWidget : public QGroupBox
{
  Q_OBJECT

public:
  ClueWidget(const QString& title, QWidget *parent = 0);

signals:
  void textChanged(const QString& str);

private slots:
  void proxyTextChanged(const QString &str);

private:
  QLineEdit *clue, *answer;
  ClueHighlighter *highlighter;
};

#endif
