/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2018 James McCoy <jamessan@jamessan.com>
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

#include "acrostica/MessageWidget.h"

#include <memory>

#include <QtWidgets>

#include "acrostica/acrostic.h"

namespace acrostica
{

MessageWidget::MessageWidget(QWidget *parent)
  : QGroupBox(tr("Message"), parent)
  , textEdit_(new QPlainTextEdit(this))
{
  textEdit_->setTabChangesFocus(true);
  connect(textEdit_, &QPlainTextEdit::textChanged,
          this, [=](){ emit textChanged(textEdit_->toPlainText()); });

  auto policy = textEdit_->sizePolicy();
  policy.setVerticalPolicy(QSizePolicy::Minimum);
  textEdit_->setSizePolicy(policy);
  auto layout = new QVBoxLayout(this);
  layout->addWidget(textEdit_);
}

void MessageWidget::setText(const QString &text)
{
  textEdit_->setPlainText(text);
}

}

#include "acrostica/moc_MessageWidget.cpp"
