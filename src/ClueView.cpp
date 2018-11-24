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

#include "acrostica/ClueView.h"

#include <QtWidgets>

namespace acrostica
{

ClueView::ClueView(QWidget *parent) : QTableView(parent)
{
  auto policy = sizePolicy();
  policy.setVerticalPolicy(QSizePolicy::MinimumExpanding);
  setSizePolicy(policy);

  setSortingEnabled(false);
  setCornerButtonEnabled(false);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setTabKeyNavigation(false);
  horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

  QShortcut *delclue = new QShortcut(QKeySequence::Delete, this);
  connect(delclue, &QShortcut::activated, this, &acrostica::ClueView::removeSelectedClues);
}

void ClueView::focusOutEvent(QFocusEvent *event) {
  if (event->reason() != Qt::MenuBarFocusReason
      && event->reason() != Qt::PopupFocusReason
      && event->reason() != Qt::ActiveWindowFocusReason) {
    auto selection = selectionModel();
    selection->clearSelection();
    QTableView::focusOutEvent(event);
  }
}

void ClueView::removeSelectedClues() {
  auto selection = selectionModel();
  auto indexes = selection->selectedRows();
  for (const auto& index : indexes) {
    model()->removeRows(index.row(), 1);
    window()->setWindowModified(true);
  }
}

}

#include "acrostica/moc_ClueView.cpp"
