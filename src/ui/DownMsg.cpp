/*
 * Acrostica - Simple acrostic creator
 * Copyright (C) 2016 James McCoy <jamessan@jamessan.com>
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
#include "DownMsg.h"

#include <QGroupBox>
#include <QPalette>
#include <QRegularExpression>

namespace acrostica
{
  namespace ui
  {
    downmsg::downmsg(QWidget *parent) :
      QGroupBox(tr("Down Message"), parent),
      msg(new QLineEdit(this)),
      alphaValidation(QRegularExpression("[\\p{L} ]+"))
    {
      msg->setValidator(&alphaValidation);

      setLayout(new QVBoxLayout);
      layout()->addWidget(msg);

      connect(msg, SIGNAL(editingFinished()),
              this, SLOT(proxyEditingFinished()));
      connect(msg, SIGNAL(textEdited(const QString&)),
              this, SLOT(forceUpper(const QString&)));
    }

    QString downmsg::text() const
    {
      return msg->text();
    }

    void downmsg::changeEvent(QEvent *event)
    {
      if (event->type() == QEvent::EnabledChange
          && !isEnabled())
      {
        QPalette newPalette = msg->palette();
        newPalette.setCurrentColorGroup(QPalette::Inactive);
        newPalette.setColor(QPalette::Base, Qt::lightGray);
        newPalette.setColor(QPalette::Text, Qt::black);
        msg->setPalette(newPalette);
        event->accept();
      }
      else
      {
        event->ignore();
      }
      return;
    }

    void downmsg::setFocus()
    {
      msg->setFocus();
    }

    void downmsg::forceUpper(const QString& s)
    {
      msg->setText(s.toUpper());
    }

    void downmsg::proxyEditingFinished()
    {
      emit editingFinished();
    }
  }
}
