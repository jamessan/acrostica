#include <QtWidgets>
#include "ClueWidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPlainTextEdit>

#include "ClueHighlighter.h"

ClueWidget::ClueWidget(const QString& title, QWidget *parent)
  : QGroupBox(title, parent),
    clue(new QPlainTextEdit(this)), answer(new QPlainTextEdit(this))
{
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(clue, 0, 0);
  layout->addWidget(answer, 1, 0);
  setLayout(layout);

  clue->setPlaceholderText(tr("Clue..."));
  clue->setTabChangesFocus(true);

  answer->setPlaceholderText(tr("Answer..."));
  answer->setTabChangesFocus(true);

  highlighter = new ClueHighlighter(answer->document());
}
