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

#ifndef ACROSTICA_MESSAGEBOX_H_
#define ACROSTICA_MESSAGEBOX_H_

#include <memory>

#include <QGroupBox>

#include "acrostic.h"

namespace acrostica
{

class MessageBox : public QGroupBox
{
  Q_OBJECT

public:
  MessageBox(QWidget *parent = nullptr);

signals:
  void textChanged(const QString& text);
};

}

#endif
