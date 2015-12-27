#include <QtWidgets>
#include "ClueWidget.h"

#include <QGroupBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>

#include "ClueHighlighter.h"

ClueWidget::ClueWidget(const QString& title, QWidget *parent)
  : QGroupBox(title, parent),
    clue(new QPlainTextEdit(this)), answer(new QPlainTextEdit(this))
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(clue, 0, 0);
  layout->addWidget(answer, 1, 0);
  setLayout(layout);

  clue->setPlaceholderText(tr("Clue..."));
  clue->setTabChangesFocus(true);

  answer->setPlaceholderText(tr("Answer..."));
  answer->setTabChangesFocus(true);

  highlighter = new ClueHighlighter(answer->document());

  connect(answer, SIGNAL(textChanged()),
          this, SLOT(proxyTextChanged()));
}

QString ClueWidget::toPlainText() const
{
  return answer->toPlainText();
}

void ClueWidget::proxyTextChanged()
{
  emit textChanged();
}
