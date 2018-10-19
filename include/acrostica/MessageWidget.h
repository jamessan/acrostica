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

#ifndef ACROSTICA_MESSAGEWIDGET_H_
#define ACROSTICA_MESSAGEWIDGET_H_

#include <memory>

#include <QGroupBox>

#include "acrostica/acrostic.h"

class QPlainTextEdit;

namespace acrostica
{

class Q_DECL_EXPORT MessageWidget : public QGroupBox
{
  Q_OBJECT

public:
  MessageWidget(QWidget *parent = nullptr);

  void setText(const QString& text);

signals:
  void textChanged(const QString& text);

private:
  QPlainTextEdit *textEdit_;
};

}

#endif
