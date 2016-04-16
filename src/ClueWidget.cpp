/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2014-2016 James McCoy <jamessan@jamessan.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtWidgets>
#include "ClueWidget.h"

#include <QGroupBox>
#include <QLineEdit>
#include <QSizePolicy>
#include <QString>
#include <QVBoxLayout>

ClueWidget::ClueWidget(const QString& answer, const QString& title, QWidget *parent) :
  QGroupBox(title, parent),
  clue_(new QLineEdit(this)),
  answer_(new QLineEdit(answer, this))
{
  setLayout(new QVBoxLayout);
  layout()->addWidget(clue_);
  layout()->addWidget(answer_);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  clue_->setPlaceholderText(tr("Clue..."));

  answer_->setPlaceholderText(tr("Answer..."));

  connect(answer_, SIGNAL(textChanged(const QString&)),
          this, SLOT(proxyTextChanged(const QString&)));

  startTimer(0);
}

void ClueWidget::timerEvent(QTimerEvent *event)
{
  if (receivers(SIGNAL(textChanged(const QString&))) > 0)
  {
    killTimer(event->timerId());
    emit textChanged(answer_->text());
  }
}

void ClueWidget::proxyTextChanged(const QString& str)
{
  emit textChanged(str);
}

QString ClueWidget::answer() const
{
  return answer_->text();
}

void ClueWidget::setAnswer(const QString &str)
{
  answer_->setText(str);
}
