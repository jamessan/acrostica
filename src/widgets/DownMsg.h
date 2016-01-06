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

#ifndef ACROSTICA_WIDGET_DOWNMESSAGE_
#define ACROSTICA_WIDGET_DOWNMESSAGE_

#include <QGroupBox>
#include <QRegularExpressionValidator>
#include <QString>

class QLineEdit;

namespace acrostica
{
  namespace widget
  {
    class downmsg : public QGroupBox
    {
      Q_OBJECT

    public:
      downmsg(QWidget *parent = 0);
      QString text() const;
      void toggleState();

    signals:
      void editingFinished();

    public slots:
      void setFocus();

    private slots:
      void proxyEditingFinished();

    private:
      QLineEdit *msg;
      QRegularExpressionValidator alphaValidation;
    };
  }
}

#endif
