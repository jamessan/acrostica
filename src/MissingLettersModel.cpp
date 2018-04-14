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

#include <QtWidgets>
#include "MissingLettersModel.h"

#include <algorithm>
#include <memory>

#include <QMap>
#include <QModelIndex>
#include <QString>
#include <QVector>

#include "acrostic.h"
#include "ClueWidget.h"

MissingLettersModel::MissingLettersModel(std::shared_ptr<acrostica::Acrostic> acrostic,
                                         AdditiveSource source, QWidget *parent)
  : QAbstractTableModel(parent)
  , mLetters(rowCount() * columnCount(), "")
  , mSource(source)
  , mAcrostic(acrostic)
{
  // XXX Fix handling of the non-ASCII QChars
}

QVariant MissingLettersModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (index.row() >= rowCount() || index.column() >= columnCount())
    return QVariant();

  if (role != Qt::DisplayRole)
    return QVariant();

  return mLetters[index.row() * columnCount() + index.column()];
}

QVariant MissingLettersModel::headerData(int section, Qt::Orientation orientation,
                                         int role) const
{
  return QVariant();
}

Qt::ItemFlags MissingLettersModel::flags(const QModelIndex& index) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

void MissingLettersModel::update()
{
  QMap<QChar, int> delta;

  int msgVal = (mSource == Message) ? 1 : -1;
  int clueVal = (mSource == Clues) ? 1 : -1;

  for (auto c : mAcrostic->message.toUpper())
  {
    if (c.isLetter())
    {
      delta[c] += msgVal;
    }
  }

  for (auto clue : mAcrostic->clues)
  {
    for (auto c : clue.answer.toUpper())
    {
      if (c.isLetter())
      {
        delta[c] += clueVal;
      }
    }
  }

  QVector<QString> letters(rowCount() * columnCount(), "");
  for (auto pair : delta.toStdMap())
  {
    QChar c = pair.first;
    int i = c.unicode() - 'A';
    int count = std::max(pair.second, 0);
    letters[i] = QString(count, QChar(c));
  }

  beginResetModel();
  mLetters = letters;
  endResetModel();
}
