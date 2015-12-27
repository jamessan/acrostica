#include <QtWidgets>
#include "MissingLettersUI.h"

#include <QHeaderView>

MissingLettersUI::MissingLettersUI(QWidget *parent) : QTableView(parent)
{
  // Remove distractions
  setShowGrid(false);
  horizontalHeader()->setVisible(false);
  verticalHeader()->setVisible(false);

  // Adjust size of displayed widgets
  horizontalHeader()->setStretchLastSection(true);
  horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

  // Disable editing
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setSelectionMode(QAbstractItemView::NoSelection);
}
