/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2014-2015 James McCoy <jamessan@jamessan.com>
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

#include <QFrame>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QString>
#include <QVBoxLayout>

ClueWidget::ClueWidget(char initialLetter, const QString& title, QWidget *parent) :
  QGroupBox(title, parent),
  clue_(new QLineEdit(this)),
  answer_(new QLineEdit(this)),
  initialLetter_(new QLabel(QString(initialLetter), this))
{
  QVBoxLayout *vlayout = new QVBoxLayout;
  QHBoxLayout *hlayout = new QHBoxLayout;
  vlayout->addWidget(clue_);
  hlayout->addWidget(initialLetter_);
  hlayout->addWidget(answer_);
  vlayout->addLayout(hlayout);
  setLayout(vlayout);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

  clue_->setPlaceholderText(tr("Clue..."));

  answer_->setPlaceholderText(tr("Answer..."));

  initialLetter_->setTextFormat(Qt::PlainText);
  initialLetter_->setFrameShape(QFrame::Box);

  connect(answer_, SIGNAL(textChanged(const QString&)),
          this, SLOT(proxyTextChanged(const QString&)));
}

void ClueWidget::proxyTextChanged(const QString& str)
{
  emit textChanged(str);
}
