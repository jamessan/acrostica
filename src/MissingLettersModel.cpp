#include <QtWidgets>
#include "MissingLettersModel.h"

MissingLettersModel::MissingLettersModel(QWidget *parent)
  : QAbstractTableModel(parent), letters_()
{
  for (int i = rowCount() * columnCount(); i > 0; i--)
  {
    letters_ << "";
  }
}

MissingLettersModel::MissingLettersModel(const QStringList& letters, QWidget *parent)
  : QAbstractTableModel(parent), letters_(letters)
{
  int size = rowCount() * columnCount();
  if (letters_.size() < rowCount() * columnCount())
  {
    letters_.reserve(size);
    for (int i = size - letters_.size(); i > 0; i--)
    {
      letters_ << "";
    }
  }
}

int MissingLettersModel::rowCount(const QModelIndex& parent) const
{
  return 13;
}

int MissingLettersModel::columnCount(const QModelIndex& parent) const
{
  return 2;
}

QVariant MissingLettersModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount() || index.column() >= columnCount())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  return letters_[index.row() + index.column() * rowCount()];
}

QVariant MissingLettersModel::headerData(int section, Qt::Orientation orientation,
                                         int role) const
{
  return QVariant();
}

Qt::ItemFlags MissingLettersModel::flags(const QModelIndex& index) const
{
  return Qt::ItemIsEnabled;
}
