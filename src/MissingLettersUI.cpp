/*
 * Acrostica - Simple acrostic creator
 * Copyright © 2014-2018 James McCoy <jamessan@jamessan.com>
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

#include "acrostica/MissingLettersUI.h"

#include <QtWidgets>

MissingLettersUI::MissingLettersUI(QWidget *parent) :
  QListView(parent)
{
  // Disallow focus since these widgets just provide information
  setFocusPolicy(Qt::NoFocus);

  // Adjust size of displayed widgets
  setWrapping(true);
  setFlow(QListView::LeftToRight);
  setResizeMode(QListView::Adjust);
}

#include "acrostica/moc_MissingLettersUI.cpp"
