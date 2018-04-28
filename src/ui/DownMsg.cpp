/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2016-2018 James McCoy <jamessan@jamessan.com>
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
#include "ui/DownMsg.h"

#include <QGroupBox>
#include <QPalette>
#include <QRegularExpression>

namespace acrostica
{
  namespace ui
  {
    downmsg::downmsg(QWidget *parent)
      : QGroupBox(tr("Down Message"), parent)
    {
      QLineEdit *msg = new QLineEdit(this);
      msg->setValidator(new QRegularExpressionValidator(QRegularExpression("\\p{L}*"), msg));

      setLayout(new QVBoxLayout);
      layout()->addWidget(msg);

      auto toUpper = [this, msg](const QString &s)
      {
        msg->setText(s.toUpper());
        emit textEdited(msg->text());
      };
      connect(msg, &QLineEdit::textEdited,
              this, toUpper);

      auto morphToLabel = [this, msg]()
      {
        layout()->removeWidget(msg);
        layout()->addWidget(new QLabel(msg->text()));
        msg->hide();
      };
      connect(msg, &QLineEdit::editingFinished,
              this, morphToLabel);
    }
  }
}
