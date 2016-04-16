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

#ifndef ACROSTICA_CLUEWIDGET_H
#define ACROSTICA_CLUEWIDGET_H

#include <QGroupBox>

class QLineEdit;
class QString;
class QTimerEvent;
class QWidget;

class ClueWidget : public QGroupBox
{
  Q_OBJECT

public:
  ClueWidget(const QString& answer, const QString& title, QWidget *parent = 0);

  QString answer() const;
  void setAnswer(const QString& str);

signals:
  void textChanged(const QString& str);

protected:
  void timerEvent(QTimerEvent *event);

private slots:
  void proxyTextChanged(const QString &str);

private:
  QLineEdit *clue_, *answer_;
};

#endif
