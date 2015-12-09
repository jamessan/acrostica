#include <QtWidgets>
#include "MissingLettersUI.h"

MissingLettersUI::MissingLettersUI(QWidget *parent) : QTableView(parent)
{
  // Remove distractions
  setShowGrid(false);
  horizontalHeader()->setVisible(false);
  verticalHeader()->setVisible(false);

  // Take up more space
  horizontalHeader()->setStretchLastSection(true);

  // Disable editing
  setEditTriggers(QAbstractItemView::NoEditTriggers);
  setSelectionMode(QAbstractItemView::NoSelection);
}
