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

#include "acrostica/PrintWindow.h"

#include <QtWidgets>

namespace acrostica
{

PrintWindow::PrintWindow(QWidget *parent)
  : QWidget(parent)
  , mModel(new QStringListModel(this))
  , mView(new QListView(this))
{
  setWindowFlags(Qt::Window);
  hide();

  auto title = new QLineEdit(this);
  title->setPlaceholderText(tr("Title"));
  title->setAlignment(Qt::AlignCenter);

  mView->setModel(mModel);

  auto layout = new QVBoxLayout(this);
  layout->addWidget(title);
  layout->addWidget(mView);
}

void PrintWindow::setMessage(const QString &msg)
{
  QString norm = msg.simplified();
  QStringList chars;

  for (const auto &c : norm) {
    if (c.isSpace() || c.isLetter()) {
      chars << c;
    }
  }

  mModel->setStringList(chars);
}

}

#include "acrostica/moc_PrintWindow.cpp"
