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
#include "MissingLettersUI.h"

#include <QHeaderView>

MissingLettersUI::MissingLettersUI(QWidget *parent) :
  QTableView(parent)
{
  // Remove distractions
  setShowGrid(false);
  horizontalHeader()->setVisible(false);
  verticalHeader()->setVisible(false);

  // Adjust size of displayed widgets
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  // Disable editing
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setSelectionMode(QAbstractItemView::NoSelection);
}
