#include <QtWidgets>
#include "ClueWidget.h"

#include <QGroupBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QVBoxLayout>

ClueWidget::ClueWidget(const QString& title, QWidget *parent)
  : QGroupBox(title, parent),
    clue(new QLineEdit(this)), answer(new QLineEdit(this))
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(clue);
  layout->addWidget(answer);
  setLayout(layout);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  clue->setPlaceholderText(tr("Clue..."));

  answer->setPlaceholderText(tr("Answer..."));

  connect(answer, SIGNAL(textChanged(const QString&)),
          this, SLOT(proxyTextChanged(const QString&)));
}

void ClueWidget::proxyTextChanged(const QString& str)
{
  emit textChanged(str);
}
