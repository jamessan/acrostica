#include <QtWidgets>
#include "ClueWidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPlainTextEdit>

ClueWidget::ClueWidget(const QString& title, QWidget *parent)
  : QGroupBox(title, parent),
    clue(new QPlainTextEdit(this)), answer(new QPlainTextEdit(this))
{
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(clue, 0, 0);
  layout->addWidget(answer, 1, 0);
  setLayout(layout);

  clue->setPlaceholderText(tr("Clue..."));
  answer->setPlaceholderText(tr("Answer..."));
}
