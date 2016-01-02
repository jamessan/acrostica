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

#include <QGroupBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QVBoxLayout>

ClueWidget::ClueWidget(const QString& title, QWidget *parent) :
  QGroupBox(title, parent),
  clue(new QLineEdit(this)),
  answer(new QLineEdit(this))
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
