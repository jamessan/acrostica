/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2016-2018 James McCoy <jamessan@jamessan.com>
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

#include "acrostica/ui/DownMsg.h"

#include <QRegularExpression>
#include <QtWidgets>

namespace acrostica
{
  namespace ui
  {
    downmsg::downmsg(QWidget *parent)
      : QGroupBox(tr("Down Message"), parent)
      , useLabel(false)
      , lineEdit(new QLineEdit(this))
      , label(new QLabel(this))
    {
      lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("\\p{L}*"), lineEdit));

      setLayout(new QVBoxLayout);
      layout()->addWidget(lineEdit);

      auto policy = sizePolicy();
      policy.setVerticalPolicy(QSizePolicy::Maximum);
      setSizePolicy(policy);

      label->hide();

      auto toUpper = [this](const QString &s)
      {
        lineEdit->setText(s.toUpper());
        emit textEdited(lineEdit->text());
      };
      connect(lineEdit, &QLineEdit::textEdited,
              this, toUpper);

      auto transform = [this]()
      {
        morphToLabel(lineEdit->text());
      };
      connect(lineEdit, &QLineEdit::editingFinished,
              this, transform);
    }

    void downmsg::morphToLabel(const QString &text)
    {
        layout()->removeWidget(lineEdit);
        lineEdit->hide();
        useLabel = true;

        label->setText(text);
        label->show();
        layout()->addWidget(label);
    }

    void downmsg::morphToLineEdit(const QString &text)
    {
      layout()->removeWidget(label);
      label->hide();
      useLabel = false;

      lineEdit->setText(text);
      lineEdit->show();
      layout()->addWidget(lineEdit);
    }

    void downmsg::reset(const QString &text)
    {
      if (text.isEmpty())
      {
        morphToLineEdit(text);
      }
      else
      {
        morphToLabel(text);
      }
    }

    void downmsg::mergeMsg(const QModelIndex &parent, int first, int last)
    {
      Q_UNUSED(parent);

      if (useLabel)
      {
        auto msg = label->text();
        msg.remove(first, last - first + 1);
        label->setText(msg);
      }
      else
      {
        auto msg = lineEdit->text();
        msg.remove(first, last - first + 1);
        lineEdit->setText(msg);
      }
    }

    void downmsg::mergeMsg(const QModelIndex &first, const QModelIndex &last,
                           const QVector<int> &roles)
    {
      Q_UNUSED(last);
      if (roles.contains(Qt::EditRole) || roles.contains(Qt::DisplayRole)) {
        auto model = first.model();

        int rowCount = model->rowCount();
        QString newMsg(rowCount, ' ');
        for (int row = 0; row < rowCount; row++)
        {
          auto clue = model->index(row, 1).data().toString();
          if (!clue.isEmpty())
          {
            newMsg.replace(row, 1, clue.at(0));
          }
        }

        if (useLabel)
        {
          label->setText(newMsg.toUpper());
        }
        else
        {
          lineEdit->setText(newMsg.toUpper());
        }
      }
    }
  }
}

#include "acrostica/ui/moc_DownMsg.cpp"
